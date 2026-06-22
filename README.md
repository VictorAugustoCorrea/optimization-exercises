<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8" />
</head>
<body>

<h1>Optimization Exercises</h1>

<p>
A collection of C++ exercises designed to practice code optimization and performance analysis.
</p>

<h2>Purpose</h2>
<p>
The goal of this repository is to improve skills in identifying performance bottlenecks, measuring execution time, and optimizing existing code while preserving correctness.
</p>

<h2>Structure</h2>
<p>Each exercise typically includes:</p>
<ul>
    <li>Problem description</li>
    <li>Baseline (inefficient) implementation</li>
    <li>Optimized implementation(s)</li>
    <li>Benchmarking code for comparison</li>
</ul>

<h2>Topics Covered</h2>
<ul>
    <li>Algorithmic complexity</li>
    <li>Memory layout and access patterns</li>
    <li>Cache locality</li>
    <li>Dynamic memory allocation</li>
    <li>Data structures</li>
    <li>Loop optimization</li>
    <li>Branch prediction</li>
    <li>Compiler optimizations</li>
    <li>SIMD and vectorization</li>
    <li>Multithreading basics</li>
</ul>

<h2>Build Example</h2>
<pre>
g++ -std=c++20 -O3 -march=native exercise{number}.cpp -o exercise
</pre>

<h2>Note</h2>
<p>
All optimizations should be validated through benchmarking. Performance improvements must be measured under representative workloads.
</p>

</body>
</html>