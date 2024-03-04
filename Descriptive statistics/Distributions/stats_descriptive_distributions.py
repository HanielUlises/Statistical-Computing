import matplotlib.pyplot as plt 
import numpy as np
from scipy import stats

# Gaussian distribution
# My arbitrary amount of discretizations
def normal_dist ():
    N = 1001

    x = np.linspace(-4, 4, N)
    gauss_distribution = stats.norm.pdf(x)

    plt.plot(x,gauss_distribution)
    plt.title('Analytical Gaussian (Normal) distribution')
    plt.show()

# Normally-distributed random numbers
def emp_norm_dis ():
    # Set of parameters
    stretch = 1     # i.e.  variance
    shift = 5       # i.e. mean
    n = 1000

    data = stretch * np.random.randn(n) + shift
    plt.hist(data, 25)
    plt.title ('Empirical Normal distribution')
    plt.show()

# Uniformly distributed numbers
def uniform_dist ():
    stretch = 2
    shift = 0.5
    n = 10000

    data = stretch * np.random.randn(n) + shift
    fig, ax = plt.subplots(2,1,figsize=(5,6))

    ax[0].plot(data,'.', markersize = 1)
    ax[0].set_title('Uniform data values')

    ax[1].hist(data, 25)
    ax[1].set_title('Uniform data histogram')

    plt.show()

# Log-normal distribution
def log_normal_dist ():
    N = 1001
    x = np.linspace(0,10,N)
    long_norm_dist = stats.lognorm.pdf(x, 1)

    plt.plot(x, long_norm_dist)
    plt.title('Logarithmically normal distribution')
    plt.show()

# Empirical log-normal distribution
def emp_log_normal_dist ():
    shift = 5
    stretch = 0.5
    n = 2000

    data = stretch * np.random.randn(n) + shift
    data = np.exp(data)

    fig, ax = plt.subplots(2,1,figsize=(4,6))
    ax[0].plot(data,'.')
    ax[0].set_title ('Log-normal data values')

    ax[1].plot(data, '.')
    ax[1].set_title ('Log-normal data histogram')

    plt.show()

# Binomial distribution
def binomial ():
    n = 10
    p = 0.5

    x = range(n+2)
    binomial_dist = stats.binom.pmf(x, n, p)

    plt.bar (x, binomial_dist)
    plt.title(f'Binomial distribution with parameters n: {n}, p: {p}')
    plt.show()

# t-test distribution
def t_test ():
    N = 1001
    df = 200
    x = np.linspace(-4, 4, N)
    t = stats.t.pdf(x, df)

    plt.plot(x,t)
    plt.xlabel('t-value')
    plt.ylabel('P(t | H$_0$)')
    plt.title(f't(%g) distribution {df}')
    plt.show()

#F distribution
def f_dist ():
    N = 1001
    num_df = 5
    den_df = 100

    x = np.linspace(0,10,N)

    fdist = stats.f.pdf(x, num_df, den_df)

    plt.plot(x, fdist)
    plt.title(f'F({num_df}, {den_df}) distribution')
    plt.xlabel('F value')
    plt.show()

def main():
    print("Choose an option:")
    print("a) Gaussian (normal) distribution")
    print("b) Empirical normal distribution")
    print("c) Uniform distribution")
    print("d) Log-Normal distribution")
    print("e) Empirical log-normal distribution")
    print("f) Binomial distribution")
    print("g) T-test")
    print("h) F distribution\n")
    option = input ()

    if option == 'a':
        normal_dist()
    elif option == 'b':
        emp_norm_dis()
    elif option == 'c':
        uniform_dist()
    elif option == 'd':
        log_normal_dist ()
    elif option == 'e':
        emp_log_normal_dist ()
    elif option == 'f':
        binomial ()
    elif option == 'g':
        t_test ()
    elif option == 'h':
        f_dist ()

if __name__ == '__main__':
    main()