import sys


def create_domain_file(domain_file_name, n_, m_):
    disks = ['d_%s' % i for i in list(range(n_))]  # [d_0,..., d_(n_ - 1)]
    pegs = ['p_%s' % i for i in list(range(m_))]  # [p_0,..., p_(m_ - 1)]
    domain_file = open(domain_file_name, 'w')  # use domain_file.write(str) to write to domain_file
    domain_file.write("Propositions:")
    domain_file.write("\n")
    for i1 in range(n):
        for i2 in range(i1+1,n+1):
            #every ring that can be on bigger one
            domain_file.write("d" + str(i1) + "_on_d" + str(i2) + " ")
        #who's at the top of the pile
        for p in range(m):
            domain_file.write("d" + str(i1) + "_top_p" + str(p) + " ")
    #empty piles
    for p1 in range(m):
        domain_file.write("d" + str(n) + "_top_p" + str(p) + " ")
    domain_file.write("\n")
    #writing the actions
    domain_file.write("Action\n")
    for i in range(m):
        for j in range(m):
            if(i==j):
                continue
            for k in range(n):
                for l1 in range(k+1,n+1):
                    for l2 in range(k+1,n+1):
                        if(l1==l2):
                            continue
                        domain_file.write("Name: d" + str(k) + "_on_d" +
                                          str(l1) +
                                          "_in_p" + str(i) +\
                                                    "_to_d" + str(l2) +
                                          "_in_p" + str(j))
                        domain_file.write("\n")
                        domain_file.write("pre: d" + str(k) + "_top_p" +
                                          str(i) + " "
                                                                        "d"
                                          + str(k) + \
                                                   "_on_d" + str(l1) + " d"
                                          + str(l2) + \
                                                           "_top_p" + str(j))
                        domain_file.write("\n")
                        domain_file.write("add: d" + str(k) + "_top_p" +
                                          str(j) + " d" +
                                          str(l1) + \
                                                   "_top_p" + str(i) + " d"
                                          + str(k) + \
                                                            "_on_d" + str(l2))
                        domain_file.write("\n")
                        domain_file.write("delete: d" + str(k) + "_top_p" +
                                          str(i) +
                                          " d" + str(k) + \
                                                      "_on_d" + str(l1) + " "
                                                                          "d" +
                                          str(l2) + \
                                                              "_top_p" +
                                          str(j))
                        domain_file.write("\n")

    domain_file.close()


def create_problem_file(problem_file_name_, n_, m_):
    disks = ['d_%s' % i for i in list(range(n_))]  # [d_0,..., d_(n_ - 1)]
    pegs = ['p_%s' % i for i in list(range(m_))]  # [p_0,..., p_(m_ - 1)]
    problem_file = open(problem_file_name_, 'w')  # use problem_file.write(str) to write to problem_file
    problem_file.write("Initial state: ")
    #top of the piles
    problem_file.write("d0_top_p0")
    problem_file.write(" ")
    for p1 in range(1,m_):
        problem_file.write("d" + str(n_) + "_top_p" + str(p1))
        problem_file.write(" ")
    #assending order
    for d1 in range(n_):
        problem_file.write("d" + str(d1) + "_on_d" + str(d1+1))
        problem_file.write(" ")
    problem_file.write("\n")
    problem_file.write("Goal state: ")
    # top of the piles
    for p1 in range(m_-1):
        problem_file.write("d" + str(n_) + "_top_p" + str(p1))
        problem_file.write(" ")
    problem_file.write("d0_top_p" + str(m_ - 1))
    problem_file.write(" ")
    # assending order
    for d1 in range(n_):
        problem_file.write("d" + str(d1) + "_on_d" + str(d1 + 1))
        problem_file.write(" ")
    problem_file.write("\n")
    problem_file.close()


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: hanoi.py n m')
        sys.exit(2)

    n = int(float(sys.argv[1]))  # number of disks
    m = int(float(sys.argv[2]))  # number of pegs

    domain_file_name = 'hanoi_%s_%s_domain.txt' % (n, m)
    problem_file_name = 'hanoi_%s_%s_problem.txt' % (n, m)

    create_domain_file(domain_file_name, n, m)
    create_problem_file(problem_file_name, n, m)
