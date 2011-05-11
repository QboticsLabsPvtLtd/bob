#ifndef KMEANSTRAINER_H
#define KMEANSTRAINER_H

#include "machine/KMeansMachine.h"
#include "machine/FrameSample.h"
#include "trainer/Sampler.h"
#include "trainer/EMTrainer.h"

namespace Torch {
namespace trainer {

/// Trains a KMeans machine.
/// @brief This class implements the expectation-maximisation algorithm for a k-means machine.
/// @details See Section 9.1 of Bishop, "Pattern recognition and machine learning", 2006
///          It uses a random initialisation of the means followed by the expectation-maximization algorithm
class KMeansTrainer : public EMTrainer<Torch::machine::KMeansMachine, Torch::machine::FrameSample>
{
public:
  
  /// Constructor
  KMeansTrainer(double convergence_threshold = 0.001, int max_iterations = 10);
  
  virtual ~KMeansTrainer() {}


  /// Initialise the means randomly. 
  /// Data is split into as many chunks as there are means, 
  /// then each mean is set to a random example within each chunk.
  void initialization(Torch::machine::KMeansMachine& kMeansMachine, const Sampler<Torch::machine::FrameSample>& sampler);
  
  /// Accumulate across the dataset:
  /// - zeroeth and first order statistics
  /// - average distance from the closest mean 
  /// Implements EMTrainer::eStep(double &)
  double eStep(Torch::machine::KMeansMachine& kmeans, const Sampler<Torch::machine::FrameSample>& data);
  
  void mStep(Torch::machine::KMeansMachine& kmeans, const Sampler<Torch::machine::FrameSample>&);
  
  /// Reset the statistics accumulators
  /// to the correct size and a value of zero.
  bool resetAccumulators(Torch::machine::KMeansMachine& kMeansMachine);

  /// Set the seed used to genrated pseudo-random numbers
  void setSeed(int seed);

  /// Get the seed
  int getSeed();
  
protected:

  /// Seed used to genrated pseudo-random numbers
  int seed;
  
  /// Zeroeth order statistics accumulator.
  /// The k'th value in m_zeroethOrderStats is the denominator of 
  /// equation 9.4, Bishop, "Pattern recognition and machine learning", 2006
  blitz::Array<double,1> m_zeroethOrderStats;

  /// First order statistics accumulator.
  /// The k'th row of m_firstOrderStats is the numerator of 
  /// equation 9.4, Bishop, "Pattern recognition and machine learning", 2006
  blitz::Array<double,2> m_firstOrderStats;
};

}
}

#endif // KMEANSTRAINER_H