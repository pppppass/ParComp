
# coding: utf-8

# In[1]:


import time
import numpy
from matplotlib import pyplot
import samp


# In[2]:


def calc_log_line(start, end, intc, order):
    return [start, end], [intc, intc * (end / start)**order]


# In[3]:


def filter_array(array, lower):
    l = []
    for e in array:
        if e > lower:
            l.append(e)
        else:
            l.append(numpy.infty)
    return l


# In[4]:


a_std = 1.5065918849


# In[5]:


m = 10


# In[6]:


ns = [2, 3, 4, 6, 8, 11, 16, 23, 32, 45, 64, 91, 128, 181, 256, 362, 512, 724, 1024, 1448, 2048, 2896, 4096, 5793, 8192]
ls = [16384, 32768, 65536, 131072]
m1s, m2s, ts = ([numpy.zeros(len(ns)) for _ in ls]for _ in range(3))


# In[31]:


for k, l in enumerate(ls):
    for i, n in enumerate(ns):
        for j in range(m):
            start = time.time()
            a = 9.0 - 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 2*n, n, 0, l, 4, numpy.random.randint(0, 2147483647) + j)
            end = time.time()
            m1s[k][i] += a
            m2s[k][i] += a**2
            ts[k][i] += end - start
        print("n = {} finished".format(n))
    m1s[k] /= m
    m2s[k] /= m
    ts[k] /= m
    print("l = {} finished".format(l))


# In[33]:


pyplot.figure(figsize=(6.0, 4.0))
for i, l in enumerate(ls):
    pyplot.plot(ns, numpy.abs(m1s[i] - a_std), label="$ L = {} $".format(l), color="C{}".format(i))
    pyplot.plot(ns, numpy.sqrt(m2s[i] - m1s[i]**2), color="C{}".format(i), linestyle="--")
    pyplot.scatter(ns, numpy.abs(m1s[i] - a_std), s=2.0, color="C{}".format(i))
    pyplot.scatter(ns, numpy.sqrt(m2s[i] - m1s[i]**2), s=2.0, color="C{}".format(i))
pyplot.xlabel("$n$")
pyplot.ylabel("Value")
pyplot.semilogx()
pyplot.semilogy()
pyplot.legend()
pyplot.savefig("Figure1.pgf")
pyplot.show()
pyplot.close()


# In[ ]:


pyplot.figure(figsize=(6.0, 4.0))
for i, l in enumerate(ls):
    pyplot.plot(ns, ts[i], label="$ L = {} $".format(l), color="C{}".format(i))
pyplot.xlabel("$n$")
pyplot.ylabel("Time")
pyplot.semilogx()
pyplot.semilogy()
pyplot.legend()
pyplot.savefig("Figure2.pgf")
pyplot.show()
pyplot.close()


# In[34]:


ns = [2, 3, 4, 6, 8, 11, 16, 23, 32, 45, 64, 91, 128, 181, 256, 362, 512, 724, 1024, 1448, 2048, 2896, 4096, 5793, 8192]
ls = [1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072]
m1s, m2s, ts = ([numpy.zeros(len(ns)) for _ in ls]for _ in range(3))


# In[35]:


for k, l in enumerate(ls):
    for i, n in enumerate(ns):
        for j in range(m):
            start = time.time()
            a = 9.0 - 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 2*n, n, l // 2, l, 4, numpy.random.randint(0, 2147483647) + j)
            end = time.time()
            m1s[k][i] += a
            m2s[k][i] += a**2
            ts[k][i] += end - start
        print("n = {} finished".format(n))
    m1s[k] /= m
    m2s[k] /= m
    ts[k] /= m
    print("l = {} finished".format(l))


# In[38]:


pyplot.figure(figsize=(6.0, 4.0))
for i, l in enumerate(ls):
    pyplot.plot(ns, filter_array(numpy.sqrt(m2s[i] - m1s[i]**2), 1.0e-8), label="$ L = {} $".format(l), color="C{}".format(i))
    pyplot.scatter(ns, filter_array(numpy.sqrt(m2s[i] - m1s[i]**2), 1.0e-8), s=2.0, color="C{}".format(i))
pyplot.xlabel("$n$")
pyplot.ylabel("Standard deviation")
pyplot.semilogx()
pyplot.semilogy()
pyplot.legend()
pyplot.savefig("Figure3.pgf")
pyplot.show()
pyplot.close()


# In[7]:


m1s, m2s, ts = [], [], []
titles = ["Stratified & 1024", "Stratified & 2048", "Stratified & 4096",  "Multi-level & 1024", "Multi-level & 2048"]


# In[8]:


m1, m2, t = 0.0, 0.0, 0.0
for _ in range(m):
    a = 9.0
    start = time.time()
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 2048, 1024, 0, 131072, 4, 1 + numpy.random.randint(0, 2147483647))
    end = time.time()
    m1 += a
    m2 += a**2
    t += end - start
    print("Time : {}".format(end - start))
m1 /= m
m2 /= m
t /= m
m1s.append(m1), m2s.append(m2), ts.append(t)


# In[9]:


m1, m2, t = 0.0, 0.0, 0.0
for _ in range(m):
    a = 9.0
    start = time.time()
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 4096, 2048, 0, 131072, 4, 1 + numpy.random.randint(0, 2147483647))
    end = time.time()
    m1 += a
    m2 += a**2
    t += end - start
    print("Time : {}".format(end - start))
m1 /= m
m2 /= m
t /= m
m1s.append(m1), m2s.append(m2), ts.append(t)


# In[10]:


m1, m2, t = 0.0, 0.0, 0.0
for _ in range(m):
    a = 9.0
    start = time.time()
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 8192, 4096, 0, 131072, 4, 1 + numpy.random.randint(0, 2147483647))
    end = time.time()
    m1 += a
    m2 += a**2
    t += end - start
    print("Time : {}".format(end - start))
m1 /= m
m2 /= m
t /= m
m1s.append(m1), m2s.append(m2), ts.append(t)


# In[11]:


m1, m2, t = 0.0, 0.0, 0.0
for _ in range(m):
    start = time.time()
    a = 9.0
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 2048, 1024, 32768, 131072, 4, 1 + numpy.random.randint(0, 2147483647))
    print("Step 1 finished")
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 4096, 2048, 8192, 32768, 4, 2 + numpy.random.randint(0, 2147483647))
    print("Step 2 finished")
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 8192, 4096, 0, 8192, 4, 3 + numpy.random.randint(0, 2147483647))
    print("Step 3 finished")
    end = time.time()
    m1 += a
    m2 += a**2
    t += end - start
    print("Time : {}".format(end - start))
m1 /= m
m2 /= m
t /= m
m1s.append(m1), m2s.append(m2), ts.append(t)


# In[12]:


m1, m2, t = 0.0, 0.0, 0.0
for _ in range(m):
    start = time.time()
    a = 9.0
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 4096, 2048, 32768, 131072, 4, 1 + numpy.random.randint(0, 2147483647))
    print("Step 1 finished")
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 8192, 4096, 8192, 32768, 4, 2 + numpy.random.randint(0, 2147483647))
    print("Step 2 finished")
    a -= 2.0 * samp.wrapper_calc_area(-2.0, 1.0, 0.0, 1.5, 16384, 8192, 0, 8192, 4, 3 + numpy.random.randint(0, 2147483647))
    print("Step 3 finished")
    end = time.time()
    m1 += a
    m2 += a**2
    t += end - start
    print("Time : {}".format(end - start))
m1 /= m
m2 /= m
t /= m
m1s.append(m1), m2s.append(m2), ts.append(t)


# In[14]:


with open("Table1.tbl", "w") as f:
    for i, title in enumerate(titles):
        f.write("{} & {:.5e} & {:.5e} & {:.5f} \\\\\n".format(title, m1s[i] - a_std, numpy.sqrt(m2s[i] - m1s[i]**2), ts[i]))
        f.write("\\hline\n")

