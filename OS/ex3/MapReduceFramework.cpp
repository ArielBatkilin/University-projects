//
// Created by nir.vaknin on 17/05/2020.
//
#include <pthread.h>
#include <atomic>
#include "MapReduceFramework.h"
#include "Barrier.h"
#include <cmath>
#include <iostream>

#define SYS_ERR "system error: "
#define THREAD_CREATE_ERR "unable to create thread"
#define FAILURE 1

using std::vector;


struct JobInfo
{
	/**
	 * This is a context job constructor
	 * @param thread_vec A vector of pthread_t
	 * @param threadsNum Threads number
	 * @param k2_keys Vector of K2
	 * @param finalIntermediateVec A vector that contains Intermediate values.
	 * @param state_mutex State mutex
	 * @param output_mutex Output mutex
	 * @param map_shuffle_barrier A barrier for the map threads
	 * @param intermidiate_pairs_mutex Intermediate pairs mutex
	 * @param k1_counter A counter of k1 values.
	 * @param k2_counter A counter of k2 values.
	 * @param shuffled_counter A counter for shuffle.
	 * @param inputVec The input vector of the program
	 * @param outputVec The output vector of the program
	 * @param mapReduceClient A mapReduceClient object
	 * @param isthread0 A bool which indicates if the thread is a shuffle thread
	 * @param jobState The state of the job.
	 */
	JobInfo(vector<pthread_t> *thread_vec, int threadsNum, vector<K2 *>
	*k2_keys, IntermediateMap
			*finalIntermediateVec, pthread_mutex_t *state_mutex,
			pthread_mutex_t *output_mutex, Barrier *map_shuffle_barrier,
			pthread_mutex_t *intermidiate_pairs_mutex,
			std::atomic<int> *k1_counter, std::atomic<int> *k2_counter,
			std::atomic<int> *shuffled_counter,
			const InputVec *inputVec,
			OutputVec *outputVec, const MapReduceClient *mapReduceClient,
			bool isthread0, JobState *jobState) :
			k1_counter(k1_counter), k2_counter(k2_counter), inputVec
			(inputVec), outputVec(outputVec),
			mapReduceClient(mapReduceClient),
			isthread0(isthread0), jobOfAllThreads(nullptr), intermediateVec(nullptr),
			map_shuffle_barrier(map_shuffle_barrier),
			intermidiate_pairs_mutex(intermidiate_pairs_mutex),
			finalIntermediateVec(finalIntermediateVec), output_mutex
					(output_mutex), k2_keys(k2_keys), threads_num(threadsNum),
			thread_vec(thread_vec), jobState(jobState), state_mutex(state_mutex),
			shuffled_counter(shuffled_counter), mutexes_intermidiates(nullptr),
			isWaitJobCalled(false)
	{
		intermediateVec = new vector<IntermediatePair>();
	}

	/**
	 * A function which sets all the job information of the program.
	 * @param vec A vector of all the job information.
	 */
	void set_vec_array(vector<JobInfo *> *vec)
	{
		jobOfAllThreads = vec;
	}

	void set_mutexes_intermidiates_vec(vector<pthread_mutex_t *> *mutexes_intermidiates_vec)
	{
		mutexes_intermidiates = mutexes_intermidiates_vec;
	}


	// Counter for the InputVec index
	std::atomic<int> *k1_counter;
	std::atomic<int> *shuffled_counter;
	std::atomic<int> *k2_counter;


	vector<pthread_t> *thread_vec;
	pthread_mutex_t *state_mutex;
	pthread_mutex_t *output_mutex;
	const InputVec *inputVec;
	OutputVec *outputVec;
	const MapReduceClient *mapReduceClient;
	int threads_num;

	bool isthread0;

	vector<JobInfo *> *jobOfAllThreads;

	// vector for each thread
	vector<IntermediatePair> *intermediateVec;

	JobState *jobState;

	Barrier *map_shuffle_barrier;
	pthread_mutex_t *intermidiate_pairs_mutex;
	IntermediateMap *finalIntermediateVec;
	vector<pthread_mutex_t *> *mutexes_intermidiates;
	vector<K2 *> *k2_keys;


	bool isWaitJobCalled;


};


/**
 * A function that does the map job
 * @param arg A void pointer which indicates the job information
 */
void map_job(void *arg)
{
	auto *jobInfo = (JobInfo *) arg;
	while (!(jobInfo->isthread0) && (*(jobInfo->k1_counter) < jobInfo->inputVec->size()))
	{
		pthread_mutex_lock(jobInfo->intermidiate_pairs_mutex);
		int old_value = (*(jobInfo->k1_counter))++;
		if (old_value == jobInfo->inputVec->size())
		{
			(*(jobInfo->k1_counter))--;
			pthread_mutex_unlock(jobInfo->intermidiate_pairs_mutex);
			break;
		}
		InputVec vec = *jobInfo->inputVec;
		jobInfo->mapReduceClient->map(vec[old_value].first, vec[old_value].second, jobInfo);
		pthread_mutex_unlock(jobInfo->intermidiate_pairs_mutex);
		pthread_mutex_lock(jobInfo->state_mutex);
		if (!((*(jobInfo->k1_counter)) == jobInfo->inputVec->size()))
		{
			jobInfo->jobState->stage = MAP_STAGE;
			jobInfo->jobState->percentage =
					((float) (*(jobInfo->k1_counter)) / (float) jobInfo->inputVec->size()) * 100;
		}
		pthread_mutex_unlock(jobInfo->state_mutex);
	}
}

/**
 * A function that does the shuffle job
 * @param arg A void pointer which indicates the job information
 */
void shuffle_job(void *arg)
{
	auto *jobInfo = (JobInfo *) arg;
	while (*(jobInfo->k1_counter) < jobInfo->inputVec->size())
	{
		for (auto &myJob : *(jobInfo->jobOfAllThreads))
		{
			pthread_mutex_lock(myJob->intermidiate_pairs_mutex);
			for (auto pair: *myJob->intermediateVec)
			{
				(*(jobInfo->shuffled_counter))++;
				(*(jobInfo->finalIntermediateVec))[pair.first].push_back(pair.second);
			}
			myJob->intermediateVec->clear();
			pthread_mutex_unlock(myJob->intermidiate_pairs_mutex);
		}
	}
	for (auto &myJob1 : *(jobInfo->jobOfAllThreads))
	{
		pthread_mutex_lock(myJob1->intermidiate_pairs_mutex);
		for (auto pair: *myJob1->intermediateVec)
		{
			(*(jobInfo->shuffled_counter))++;
			(*(jobInfo->finalIntermediateVec))[pair.first].push_back(pair.second);
		}
		myJob1->intermediateVec->clear();
		pthread_mutex_unlock(myJob1->intermidiate_pairs_mutex);
	}
	for (auto const &pair: *jobInfo->finalIntermediateVec)
	{
		jobInfo->k2_keys->push_back(pair.first);
	}
}


/**
 * A function that does the reduce job
 * @param arg A void pointer which indicates the job information
 */
void reduce_job(void *arg)
{
	auto *jobInfo = (JobInfo *) arg;
	while (*(jobInfo->k2_counter) < jobInfo->finalIntermediateVec->size())
	{
		int old_value = (*(jobInfo->k2_counter))++;
		if (old_value >= jobInfo->finalIntermediateVec->size())
		{
			(*(jobInfo->k2_counter))--;
			break;
		}
		jobInfo->mapReduceClient->reduce((*(jobInfo->k2_keys))[old_value],
										 (*(jobInfo->finalIntermediateVec))[(*(jobInfo->k2_keys))
										 [old_value]], arg);
		if (jobInfo->jobState->stage != REDUCE_STAGE)
		{
			jobInfo->jobState->stage = REDUCE_STAGE;
		}
		pthread_mutex_lock(jobInfo->state_mutex);
		if (!(*(jobInfo->k2_counter) > jobInfo->finalIntermediateVec->size()))
		{
			jobInfo->jobState->percentage = ((float) (*(jobInfo->k2_counter)) / (float)
					jobInfo->finalIntermediateVec->size()) * 100;
		}
		pthread_mutex_unlock(jobInfo->state_mutex);
	}
}

/**
 * A function that does the whole program job.
 * @param arg A void pointer which indicates the job information
 */
void *startThreadJob(void *arg)
{
	auto *jobInfo = (JobInfo *) arg;
	pthread_mutex_lock(jobInfo->state_mutex);
	if (jobInfo->jobState->stage == UNDEFINED_STAGE)
	{
		jobInfo->jobState->stage = MAP_STAGE;
	}
	pthread_mutex_unlock(jobInfo->state_mutex);
	map_job(arg);
	if (jobInfo->isthread0)
	{
		shuffle_job(arg);
		pthread_mutex_lock(jobInfo->state_mutex);
		jobInfo->jobState->stage = SHUFFLE_STAGE;
		jobInfo->jobState->percentage = 100;
		pthread_mutex_unlock(jobInfo->state_mutex);
	}
	jobInfo->map_shuffle_barrier->barrier();
	pthread_mutex_lock(jobInfo->state_mutex);
	if (jobInfo->jobState->stage != REDUCE_STAGE)
	{
		jobInfo->jobState->stage = REDUCE_STAGE;
	}
	pthread_mutex_unlock(jobInfo->state_mutex);
	reduce_job(arg);
	return nullptr;
}

JobHandle
startMapReduceJob(const MapReduceClient &client, const InputVec &inputVec, OutputVec &outputVec,
				  int multiThreadLevel)
{
	auto *k2_keys = new vector<K2 *>;
	auto *finalIntermediateVec = new IntermediateMap;
	auto *output_mutex = new pthread_mutex_t(PTHREAD_MUTEX_INITIALIZER);
	auto *state_mutex = new pthread_mutex_t(PTHREAD_MUTEX_INITIALIZER);
	auto *mutexes_intermidiates = new vector<pthread_mutex_t *>(
			multiThreadLevel - 1);
	for (int i = 0; i < multiThreadLevel - 1; ++i)
	{
		(*mutexes_intermidiates)[i] = new pthread_mutex_t(PTHREAD_MUTEX_INITIALIZER);
	}
	auto *map_shuffle_barrier = new Barrier(multiThreadLevel);
	auto *thread_vec = new vector<pthread_t>(multiThreadLevel);
	auto *vecJobInfo = new vector<JobInfo *>(multiThreadLevel - 1);
	auto *jobState = new JobState();
	jobState->stage = MAP_STAGE;
	jobState->percentage = 0;
	auto *k1_counter = new std::atomic<int>(0);
	auto *shuffled_counter = new std::atomic<int>(0);
	auto *k2_counter = new std::atomic<int>(0);
	for (int i = 1; i < multiThreadLevel; ++i)
	{
		auto *jobInfo = new JobInfo{thread_vec, multiThreadLevel, k2_keys,
									finalIntermediateVec, state_mutex,
									output_mutex,
									map_shuffle_barrier,
									(*mutexes_intermidiates)[i - 1],
									k1_counter, k2_counter, shuffled_counter, &inputVec,
									&outputVec, &client,
									false, jobState};
		int ret_value = pthread_create(&(*thread_vec)[i], nullptr, startThreadJob, jobInfo);
		if (ret_value)
		{
			std::string s = SYS_ERR;
			s += THREAD_CREATE_ERR;
			std::cerr << s << std::endl;
			exit(FAILURE);
		}
		(*vecJobInfo)[i - 1] = jobInfo;
	}
	auto *shuffle = new JobInfo{thread_vec, multiThreadLevel, k2_keys, finalIntermediateVec,
								state_mutex,
								output_mutex, map_shuffle_barrier,
								nullptr, k1_counter,
								k2_counter, shuffled_counter,
								&inputVec, &outputVec, &client, true, jobState};
	shuffle->set_vec_array(vecJobInfo);
	shuffle->set_mutexes_intermidiates_vec(mutexes_intermidiates);
	int ret_value = pthread_create(&(*thread_vec)[0], nullptr, startThreadJob, shuffle);
	if (ret_value)
	{
		std::string s = SYS_ERR;
		s += THREAD_CREATE_ERR;
		std::cerr << s << std::endl;
		exit(FAILURE);
	}
	return shuffle;
}

void waitForJob(JobHandle job)
{
	auto *jobInfo = (JobInfo *) job;
	for (int i = 0; i < jobInfo->threads_num; ++i)
	{
		if (i != 0)
		{
			if ((!(((*(jobInfo->jobOfAllThreads))[i - 1])->isWaitJobCalled)))
			{
				pthread_join((*(jobInfo->thread_vec))[i], nullptr);
				((*(jobInfo->jobOfAllThreads))[i - 1])->isWaitJobCalled = true;
			}
		}
		else
		{
			if (!(jobInfo->isWaitJobCalled))
			{
				pthread_join((*(jobInfo->thread_vec))[i], nullptr);
				jobInfo->isWaitJobCalled = true;
			}
		}
	}
}

void getJobState(JobHandle job, JobState *state)
{
	auto *my_job = (JobInfo *) job;
	pthread_mutex_lock(my_job->state_mutex);
	*state = *my_job->jobState;
	pthread_mutex_unlock(my_job->state_mutex);
}


void closeJobHandle(JobHandle job)
{
	waitForJob(job);
	auto *jobInfo = (JobInfo *) job;
	delete jobInfo->k1_counter;
	delete jobInfo->k2_counter;
	delete jobInfo->shuffled_counter;
	pthread_mutex_destroy(jobInfo->state_mutex);
	pthread_mutex_destroy(jobInfo->output_mutex);
	delete jobInfo->output_mutex;
	delete jobInfo->state_mutex;
	delete jobInfo->map_shuffle_barrier;
	delete jobInfo->jobState;
	delete jobInfo->k2_keys;
	delete jobInfo->thread_vec;
	delete jobInfo->finalIntermediateVec;
	delete jobInfo->intermediateVec;
	delete jobInfo->mutexes_intermidiates;
	for (auto job_info : (*jobInfo->jobOfAllThreads))
	{
		pthread_mutex_destroy(job_info->intermidiate_pairs_mutex);
		delete job_info->intermidiate_pairs_mutex;
		delete job_info->intermediateVec;
		delete job_info;
	}
	delete jobInfo->jobOfAllThreads;
	delete jobInfo;
}

void emit2(K2 *key, V2 *value, void *context)
{
	auto *jobInfo = (JobInfo *) context;
	IntermediatePair pair = {key, value};
	pthread_mutex_lock(jobInfo->state_mutex);
	jobInfo->intermediateVec->push_back(pair);
	pthread_mutex_unlock(jobInfo->state_mutex);
}

void emit3(K3 *key, V3 *value, void *context)
{
	auto *jobInfo = (JobInfo *) context;
	pthread_mutex_lock(jobInfo->output_mutex);
	jobInfo->outputVec->push_back(std::make_pair(key, value));
	pthread_mutex_unlock(jobInfo->output_mutex);
}

