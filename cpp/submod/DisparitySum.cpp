#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "../utils/helper.h"

#include "DisparitySum.h"

// Note to self: Migrate all parameter related sanity/error checks from C++ FL
// to Python FL

DisparitySum::DisparitySum() {}

// For dense mode
DisparitySum::DisparitySum(ll n_, std::string mode_,
                           std::vector<std::vector<float>> k_dense_,
                           ll num_neighbors_, bool partial_,
                           std::unordered_set<ll> ground_) {
    if (mode_ != "dense") {
        std::cerr << "Error: Incorrect mode specified for the provided dense "
                     "similarity matrix\n";
        return;
    }

    if (k_dense_.size() == 0) {
        std::cerr << "Error: Empty similarity matrix\n";
        return;
    }

    n = n_;
    mode = mode_;
    k_dense = k_dense_;
    num_neighbors = num_neighbors_;
    partial = partial_;
    // Populating effectiveGroundSet
    if (partial == true) {
        effectiveGroundSet = ground_;
    } else {
        for (ll i = 0; i < n; ++i) {
            effectiveGroundSet.insert(i);  // each insert takes O(log(n)) time
        }
    }

    numEffectiveGroundset = effectiveGroundSet.size();
    currentSum = 0;
}

// For sparse mode
DisparitySum::DisparitySum(ll n_, std::string mode_, std::vector<float> arr_val,
                           std::vector<ll> arr_count, std::vector<ll> arr_col,
                           ll num_neighbors_, bool partial_,
                           std::unordered_set<ll> ground_) {
    // std::cout<<n_<<" "<<mode_<<" "<<num_neighbors_<<" "<<partial_<<"\n";
    if (mode_ != "sparse") {
        std::cerr << "Error: Incorrect mode specified for the provided sparse "
                     "similarity matrix\n";
        return;
    }

    if (arr_val.size() == 0 || arr_count.size() == 0 || arr_col.size() == 0) {
        std::cerr << "Error: Empty/Corrupt sparse similarity matrix\n";
        return;
    }

    n = n_;
    mode = mode_;
    k_sparse = SparseSim(arr_val, arr_count, arr_col);
    num_neighbors = num_neighbors_;
    partial = partial_;
    // Populating effectiveGroundSet
    if (partial == true) {
        effectiveGroundSet = ground_;
    } else {
        for (ll i = 0; i < n; ++i) {
            effectiveGroundSet.insert(i);  // each insert takes O(log(n)) time
        }
    }

    numEffectiveGroundset = effectiveGroundSet.size();
    currentSum = 0;
}

// helper friend function
float get_sum_dense(std::unordered_set<ll> dataset_ind, DisparitySum obj) {
    float sum = 0;
    for (auto it = dataset_ind.begin(); it != dataset_ind.end(); ++it) {
        for (auto it2 = dataset_ind.begin(); it2 != dataset_ind.end(); ++it2) {
            sum += 1 - obj.k_dense[*it][*it2];
        }
    }
    return sum / 2;
}

float get_sum_sparse(std::unordered_set<ll> dataset_ind, DisparitySum obj) {
    float sum = 0;
    for (auto it = dataset_ind.begin(); it != dataset_ind.end(); ++it) {
        for (auto it2 = dataset_ind.begin(); it2 != dataset_ind.end(); ++it2) {
            sum += 1 - obj.k_sparse.get_val(*it, *it2);
        }
    }
    return sum / 2;
}

// TODO: In all the methods below, get rid of code redundancy by merging dense
// and sparse mode blocks together
float DisparitySum::evaluate(std::unordered_set<ll> X) {
    std::unordered_set<ll> effectiveX;
    float result = 0;

    if (partial == true) {
        // effectiveX = intersect(X, effectiveGroundSet)
        // std::set_intersection(X.begin(), X.end(), effectiveGroundSet.begin(),
        //                       effectiveGroundSet.end(),
        //                       std::inserter(effectiveX, effectiveX.begin()));
        effectiveX = set_intersection(X, effectiveGroundSet);
    } else {
        effectiveX = X;
    }

    if (effectiveX.size() == 0) {
        return 0;
    }

    if (mode == "dense") {
        result = get_sum_dense(effectiveX, *this);
    } else if(mode =="sparse") {
        result = get_sum_sparse(effectiveX, *this);
    } else {
        std::cerr << "ERROR: INVALID mode\n";
    }
    return result;
}

float DisparitySum::evaluateWithMemoization(
    std::unordered_set<ll>
        X)  // assumes that memoization exists for effectiveX
{
    std::unordered_set<ll> effectiveX;
    float result = 0;

    if (partial == true) {
        // effectiveX = intersect(X, effectiveGroundSet)
        // std::set_intersection(X.begin(), X.end(), effectiveGroundSet.begin(),
        //                       effectiveGroundSet.end(),
        //                       std::inserter(effectiveX, effectiveX.begin()));
        effectiveX = set_intersection(X, effectiveGroundSet);
    } else {
        effectiveX = X;
    }
    if (effectiveX.size() == 0)  
    {
        return 0;
    }
    return currentSum;
}

float DisparitySum::marginalGain(std::unordered_set<ll> X, ll item) {
    std::unordered_set<ll> effectiveX;
    float gain = 0;

    if (partial == true) {
        // effectiveX = intersect(X, effectiveGroundSet)
        // std::set_intersection(X.begin(), X.end(), effectiveGroundSet.begin(),
        //                       effectiveGroundSet.end(),
        //                       std::inserter(effectiveX, effectiveX.begin()));
        effectiveX = set_intersection(X, effectiveGroundSet);
    } else {
        effectiveX = X;
    }

    if (effectiveX.size() == 0) {
        return 0;
    }

    if (effectiveX.find(item)!=effectiveX.end()) {
        return 0;
    }

    if(mode == "dense") {
        for (auto it = effectiveX.begin(); it != effectiveX.end(); ++it) {
            gain += 1 - k_dense[item][*it];
        }
    } else if (mode == "sparse") {
        for (auto it = effectiveX.begin(); it != effectiveX.end(); ++it) {
            gain += 1 - k_sparse.get_val(item, *it);
        }
    } else {
        std::cerr << "ERROR: INVALID mode\n";
    }
    
    return gain;
}

float DisparitySum::marginalGainWithMemoization(std::unordered_set<ll> X, ll item) {
    return marginalGain(X, item);
}

void DisparitySum::updateMemoization(std::unordered_set<ll> X, ll item) {
    currentSum += marginalGain(X, item);
}

std::unordered_set<ll> DisparitySum::getEffectiveGroundSet() {
    return effectiveGroundSet;
}

std::vector<std::pair<ll, float>> DisparitySum::maximize(
    std::string s, float budget, bool stopIfZeroGain = false,
    bool stopIfNegativeGain = false,
    bool verbose = false)  // TODO: migrate fixed things to constructor
{
    if (s == "NaiveGreedy") {
        return NaiveGreedyOptimizer().maximize(*this, budget, stopIfZeroGain,
                                               stopIfNegativeGain, verbose);
    }
}

void DisparitySum::cluster_init(ll n_, std::vector<std::vector<float>> k_dense_,
                                std::unordered_set<ll> ground_) {
    *this = DisparitySum(n_, "dense", k_dense_, -1, true, ground_);
}

void DisparitySum::clearMemoization()
{
    currentSum=0;	
}

void DisparitySum::setMemoization(std::unordered_set<ll> X)
{
    currentSum=evaluate(X);
}
