#include "VirtualMemory.h"
#include "PhysicalMemory.h"



/**
 * a struct for finding the frame we need
 */
typedef struct The_Frame
{
	uint64_t empty_table_frame_index;
	uint64_t empty_table_frame_parent;
	uint64_t max_frame_index;
	uint64_t max_cyclical_distance;
	uint64_t max_cyclical_index;
	uint64_t max_cyclic_page;
	uint64_t parent_of_max_distance;
} My_Frame;

word_t find_frame(uint64_t tree_code, word_t calling_frame);

void travel_tree(My_Frame *my_frame, int depth, uint64_t frame_index, uint64_t parent_index,
				 uint64_t page, uint64_t tree_code, word_t calling_frame);


/**
 * helper for extracting needed length offset
 * @param address - the value from him we need to extract
 * @param off_set_len - the len we need to be cuted
 */
uint64_t extractOffSet(uint64_t address, int off_set_len)
{
	uint64_t b = 1;
	for (int i = 0; i < off_set_len - 1; i++)
	{
		b = b << 1u;
		b += 1;
	}
	return address & b;
}

/**
 * clearing table of some frame
 * @param frameIndex - the frame that need to be cleared
 */
void clearTable(uint64_t frameIndex)
{
	for (uint64_t i = 0; i < PAGE_SIZE; ++i)
	{
		PMwrite(frameIndex * PAGE_SIZE + i, 0);
	}
}

/**
 * Initialize the virtual memory
 */
void VMinitialize()
{
	clearTable(0);
}

/**
 * callculate the distance
 * @param page - the page we wnt to swap in
 * @param tree_code - our tree code
 * @return the distance
 */
uint64_t calculateCyclicalDistance(uint64_t page, uint64_t tree_code)
{
	auto value1 = tree_code - page;
	auto value2 = (tree_code + 1) - (tree_code - page);
	if (value1 < value2)
	{
		return value1;
	}
	return value2;
}


/**
 * check if the virtual address is valid
 * @param virtualAddress - the virtual address to be checked
 */
bool notVirtualAdressValid(uint64_t virtualAddress)
{
	return (virtualAddress >> VIRTUAL_ADDRESS_WIDTH) != 0;
}

/**
 * translate virtual address to physical address
 * @param virtualAddress - the virtual address to be translated
 * @return physical address
 */
uint64_t translateVirtualToPhysical(uint64_t virtualAddress)
{
	uint64_t offset = extractOffSet(virtualAddress, OFFSET_WIDTH);
	uint64_t tree_code = virtualAddress >> OFFSET_WIDTH;
	word_t my_frame_index = 0;
	for (int i = 1; i <= TABLES_DEPTH; i++)
	{
		uint64_t my_page_val = extractOffSet(tree_code >> ((TABLES_DEPTH - i) * OFFSET_WIDTH),
											 OFFSET_WIDTH);
		word_t my_mid_address = 0;
		PMread(my_frame_index * PAGE_SIZE + my_page_val, &my_mid_address);
		if (my_mid_address == 0)
		{
			my_mid_address = find_frame(tree_code, my_frame_index);
			if (i == TABLES_DEPTH)
			{
				PMrestore((uint64_t) my_mid_address, tree_code);
			}
			else
			{
				clearTable(my_mid_address);
			}
			PMwrite(my_frame_index * PAGE_SIZE + my_page_val, my_mid_address);
		}
		my_frame_index = my_mid_address;
	}
	return (my_frame_index * PAGE_SIZE + offset);
}

/**
 * finding the correct frame by priority:
 * 1. A frame containing an empty table –where all rows are 0. We don’t have to evict it, but we do
 * have to remove the reference to this table from its parent
 * .2 An unused frame
 * .3 If all frames are already used, then a page must be swapped out from some frame in order to
 *   replace it with the relevant page (a table or actual page). The frame that will be chosen is the
 *   frame containing a page p such that the cyclical distance is maximal.
 *   This page must be swapped out before we use the frame, and we also have to remove the reference
 *   to this page from its parent table
 * @param tree_code - our pages
 * @param calling_frame - the frame who called this function
 * @return the needed frame
 */
word_t find_frame(uint64_t tree_code, word_t calling_frame)
{
	The_Frame target_frame = {0, 0, 0,
							  0, 0, 0,
							  0};
	travel_tree(&target_frame, 0, 0, 0, 0, tree_code, calling_frame);
	//priority 1
	if (target_frame.empty_table_frame_index != 0)
	{
		// remove refernce from parents table
		word_t value;
		for (unsigned int i = 0; i < PAGE_SIZE; ++i)
		{
			PMread(target_frame.empty_table_frame_parent * PAGE_SIZE + i, &value);
			if ((uint64_t) value == target_frame.empty_table_frame_index)
			{
				PMwrite(target_frame.empty_table_frame_parent * PAGE_SIZE + i, 0);
				break;
			}
		}
		return target_frame.empty_table_frame_index;
	}
	// priority 2
	if (target_frame.max_frame_index + 1 < NUM_FRAMES)
	{
		return target_frame.max_frame_index + 1;
	}
	// priority 3
	// // remove refernce from parents table
	word_t value;
	for (unsigned int i = 0; i < PAGE_SIZE; ++i)
	{
		PMread(target_frame.parent_of_max_distance * PAGE_SIZE + i, &value);
		if ((uint64_t) value == target_frame.max_cyclical_index)
		{
			PMwrite(target_frame.parent_of_max_distance * PAGE_SIZE + i, 0);
			break;
		}
	}
	PMevict(target_frame.max_cyclical_index, target_frame.max_cyclic_page);
	return target_frame.max_cyclical_index;
}

/**
 * check if this frames table is empty
 * @param frame_index - the frame we are checking
 * @return true if empty, false otherwise
 */
bool is_empty_table(uint64_t frame_index)
{
	word_t value;
	for (unsigned int i = 0; i < PAGE_SIZE; i++)
	{
		PMread(frame_index * PAGE_SIZE + i, &value);
		if (value != 0)
		{
			return false;
		}
	}
	return true;
}

/**
 * a recursive function that traviling in the tree, and searching for the correct frame
 * @param my_frame - struct for keeping our results
 * @param depth - the depth we corrently at
 * @param frame_index - the frame we corrently at
 * @param parent_index - the frame we corrently at parent index
 * @param page - the page we corrently at
 * @param tree_code - the pages we need
 * @param calling_frame - the frame who called us
 */
void travel_tree(My_Frame *my_frame, int depth, uint64_t frame_index, uint64_t parent_index,
				 uint64_t page, uint64_t tree_code, word_t calling_frame)
{
	// check if it is an empty table
	if (depth != TABLES_DEPTH && is_empty_table(frame_index) && frame_index !=
																(uint64_t) calling_frame)
	{
		my_frame->empty_table_frame_index = frame_index;
		my_frame->empty_table_frame_parent = parent_index;
		return;
	}
	// remember max frame index
	if (frame_index > my_frame->max_frame_index)
	{
		my_frame->max_frame_index = frame_index;
	}
	// check the cyclic distance
	if (depth == TABLES_DEPTH)
	{
		uint64_t cyclic_distance = calculateCyclicalDistance(page, tree_code);
		if (cyclic_distance > my_frame->max_cyclical_distance)
		{
			my_frame->max_cyclical_distance = cyclic_distance;
			my_frame->max_cyclical_index = frame_index;
			my_frame->max_cyclic_page = page;
			my_frame->parent_of_max_distance = parent_index;
		}
		return;
	}
	// continue searching
	word_t value;
	for (uint64_t i = 0; i < PAGE_SIZE; i++)
	{
		PMread(frame_index * PAGE_SIZE + i, &value);
		if (value != 0)
		{
			travel_tree(my_frame, depth + 1, (uint64_t) value, frame_index,
						(page << OFFSET_WIDTH) + i, tree_code, calling_frame);
			if (my_frame->empty_table_frame_index != 0)
			{
				return;
			}
		}
	}
}

/* reads a word from the given virtual address
 * and puts its content in *value.
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMread(uint64_t virtualAddress, word_t *value)
{
	if (notVirtualAdressValid(virtualAddress))
	{
		return 0;
	}
	PMread(translateVirtualToPhysical(virtualAddress), value);
	return 1;
}

/* writes a word to the given virtual address
 *
 * returns 1 on success.
 * returns 0 on failure (if the address cannot be mapped to a physical
 * address for any reason)
 */
int VMwrite(uint64_t virtualAddress, word_t value)
{
	if (notVirtualAdressValid(virtualAddress))
	{
		return 0;
	}
	uint64_t s = translateVirtualToPhysical(virtualAddress);
	PMwrite(s, value);
	return 1;
}