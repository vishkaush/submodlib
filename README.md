<p align="center">
    <br>
        &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp
        <img src="https://github.com/decile-team/submodlib/blob/master/submodlib_logo.png" width="500" />
    </br>
</p>

# About SubModLib

*SubModLib* is an easy-to-use, efficient and scalable library for submodular optimization which finds its application in summarization, data subset selection, hyper parameter tuning etc. Through a rich API, it offers a great deal of flexibility in the way it can be used.

# Salient Features

* **Rich suite of functions** for a wide variety of subset selection tasks - regular set (submodular) functions, submodular mutual information functions, conditional gain functions and conditional mutual information functions
* Supports **different types of optimizers** - naive greedy, lazy (accelerated) greedy, stochastic (random) greedy, lazier than lazy greedy
* Combines the **best of Python's ease of use and C++'s efficiency**
* **Rich API** which gives a variety of options to the user. See [this](https://colab.research.google.com/github/vishkaush/submodlib/blob/master/tutorials/Different_Options_for_Usage.ipynb) notebook for an example of different usage patterns
* De-coupled function and optimizer paradigm makes it **suitable for a wide-variety of tasks** 
* Comprehensive documentation (available [here](https://submodlib.readthedocs.io/))

# Setup

## Alternative 1
* `$ pip install -i https://test.pypi.org/simple/ --extra-index-url https://pypi.org/simple/ submodlib`

## Alternative 2 (if local docs need to be built and test cases need to be run)
* `$ git clone https://github.com/decile-team/submodlib.git`
* `$ cd submodlib`
* `$ pip install .`
* **Latest documentation** is available at [readthedocs](https://submodlib.readthedocs.io/). However, if local documentation is required to be built, follow these steps::
    * `$ pip install -U sphinx`
    * `$ pip install sphinxcontrib-bibtex`
    * `$ pip install sphinx-rtd-theme`
    * `$ cd docs`
    * `$ make clean html`
* **To run the tests**, follow these steps:
    * `$ pip install pytest`
    * `$ pytest` # this runs ALL tests
    * `$ pytest -m <marker> --verbose --disable-warnings -rA` # this runs test specified by the <marker>. Possible markers are mentioned in pyproject.toml file.

# Usage

It is very easy to get started with submodlib. Using a submodular function in submodlib essentially boils down to just two steps:

1. instantiate the corresponding function object
2. invoke the desired method on the created object

The most frequently used methods are:
1. f.evaluate() - takes a subset and returns the score of the subset as computed by the function f
2. f.marginalGain() - takes a subset and an element and returns the marginal gain of adding the element to the subset, as computed by f
3. f.maximize() - takes a budget and an optimizer to return an optimal set as a result of maximizing f

For example,
```
from submodlib import FacilityLocationFunction
objFL = FacilityLocationFunction(n=43, data=groundData, mode="dense", metric="euclidean")
greedyList = objFL.maximize(budget=10,optimizer='NaiveGreedy')
```

For a more detailed discussion on all possible usage patterns, please see [Different Options of Usage](https://colab.research.google.com/github/vishkaush/submodlib/blob/master/tutorials/Different_Options_for_Usage.ipynb)


# Functions

* [Regular set (submodular) functions](https://submodlib.readthedocs.io/en/latest/functions/submodularFunctions.html) (**for vanilla subset selection** requiring representation, diversity, importance, relevance, coverage)
    * [Facility Location](https://submodlib.readthedocs.io/en/latest/functions/facilityLocation.html)
    * [Disparity Sum](https://submodlib.readthedocs.io/en/latest/functions/disparitySum.html)
    * [Disparity Min](https://submodlib.readthedocs.io/en/latest/functions/disparityMin.html)
    * [Log Determinant](https://submodlib.readthedocs.io/en/latest/functions/logDeterminant.html)
    * [Set Cover](https://submodlib.readthedocs.io/en/latest/functions/setCover.html)
    * [Probabilistic Set Cover](https://submodlib.readthedocs.io/en/latest/functions/probabilisticSetCover.html)
    * [Graph Cut](https://submodlib.readthedocs.io/en/latest/functions/graphCut.html)
    * [Feature Based](https://submodlib.readthedocs.io/en/latest/functions/featureBased.html)
* [Submodular mutual information functions](https://submodlib.readthedocs.io/en/latest/functions/submodularMutualInformation.html) (**for query-focused subset selelction**)
    * [Facility Location Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/facilityLocationMutualInformation.html)
    * [Facility Location Variant Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/facilityLocationVariantMutualInformation.html)
    * [Graph Cut Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/graphCutMutualInformation.html)
    * [Log Determinant Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/logDeterminantMutualInformation.html)
    * [Concave Over Modular](https://submodlib.readthedocs.io/en/latest/functions/concaveOverModular.html)
    * [Set Cover Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/setCoverMutualInformation.html)
    * [Probabilistc Set Cover Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/probabilisticSetCoverMutualInformation.html)
* [Conditional gain functions](https://submodlib.readthedocs.io/en/latest/functions/conditionalGain.html) (**for query-irrelevant/privacy-preserving subset selection**)
    * [Facility Location Conditional Gain](https://submodlib.readthedocs.io/en/latest/functions/facilityLocationConditionalGain.html)
    * [Graph Cut Conditional Gain](https://submodlib.readthedocs.io/en/latest/functions/graphCutConditionalGain.html)
    * [Log Determinant Conditional Gain](https://submodlib.readthedocs.io/en/latest/functions/logDeterminantConditionalGain.html)
    * [Set Cover Conditional Gain](https://submodlib.readthedocs.io/en/latest/functions/setCoverConditionalGain.html)
    * [Probabilistic Set Cover Conditional Gain](https://submodlib.readthedocs.io/en/latest/functions/probabilisticSetCoverConditionalGain.html)
* [Conditional mutual information functions](https://submodlib.readthedocs.io/en/latest/functions/conditionalMutualInformation.html) (**for joint query-focused and privacy-preserving subset selection**)
    * [Facility Location Conditional Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/facilityLocationConditionalMutualInformation.html)
    * [Log Determinant Conditional Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/logDeterminantConditionalMutualInformation.html)
    * [Set Cover Conditional Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/setCoverConditionalMutualInformation.html)
    * [Probabilistic Set Cover Conditional Mutual Information](https://submodlib.readthedocs.io/en/latest/functions/probabilisticSetCoverConditionalMutualInformation.html)

# Modelling Capabilities of Different Functions

We demonstrate the representational power and modeling capabilities of different functions in [this](https://github.com/decile-team/submodlib/blob/master/tutorials/Representational%20Power%20of%20Different%20Functions.ipynb) notebook.

# Optimizers 

* [NaiveGreedy](https://submodlib.readthedocs.io/en/latest/optimizers/naiveGreedy.html)
* [LazyGreedy](https://submodlib.readthedocs.io/en/latest/optimizers/lazyGreedy.html)
* [StochasticGreedy](https://submodlib.readthedocs.io/en/latest/optimizers/stochasticGreedy.html)
* [LazierThanLazyGreedy](https://submodlib.readthedocs.io/en/latest/optimizers/lazierThanLazyGreedy.html)
* [This](https://github.com/decile-team/submodlib/blob/master/tutorials/Optimizers.ipynb) notebook demonstrates the use and comparison of different optimizers

# Contributors

* Vishal Kaushal

# Contact

Should you face any issues or have any feedback or suggestions, please feel free to contact vishal[dot]kaushal[at]gmail.com

# Acknowledgements 

This work is supported by the Ekal Fellowship (www.ekal.org).
