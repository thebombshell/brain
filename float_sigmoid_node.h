
#ifndef BRAIN_FLOAT_SIGMOID_NEURON_H
#define BRAIN_FLOAT_SIGMOID_NEURON_H

#include "data.h"
#include "node.h"

namespace brain
{
	typedef Data<float> FloatData;

	class FloatBiasFactorConnection : public Connection<FloatData, float>
	{
	public:

		FloatBiasFactorConnection();
		FloatBiasFactorConnection(FloatData* t_pInput);
		FloatBiasFactorConnection(const FloatBiasFactorConnection& t_other);
		~FloatBiasFactorConnection();

		void SetBias(float t_bias);
		void SetFactor(float t_factor);

		float Pull() const;
		float Bias() const;
		float Factor() const;

	private:

		float m_bias{ 0.0f };
		float m_factor{ 1.0f };
	};

	class FloatSigmoidFeedForwardNode : public FeedForwardNode<float>
	{
	public:

		FloatSigmoidFeedForwardNode();
		FloatSigmoidFeedForwardNode(FloatData* t_pData);
		FloatSigmoidFeedForwardNode(const FloatSigmoidFeedForwardNode& t_other);
		~FloatSigmoidFeedForwardNode();

		void Update();

	private:

	};
}

#endif