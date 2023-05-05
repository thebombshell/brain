
#include "float_sigmoid_node.h"

#include "activation_functions.h"

using namespace brain;

// brain::FloatBiasFactorConnection

FloatBiasFactorConnection::FloatBiasFactorConnection() : Connection{ } { }

FloatBiasFactorConnection::FloatBiasFactorConnection(FloatData* t_pInput) : Connection{ t_pInput } { }

FloatBiasFactorConnection::FloatBiasFactorConnection(const FloatBiasFactorConnection& t_other) : Connection{ t_other }, m_bias{ t_other.m_bias }, m_factor{ t_other.m_factor } { }

FloatBiasFactorConnection::~FloatBiasFactorConnection() { }

void FloatBiasFactorConnection::SetBias(float t_bias) { m_bias = t_bias; }

void FloatBiasFactorConnection::SetFactor(float t_factor) { m_factor = t_factor; }

float FloatBiasFactorConnection::Pull() const
{
	return m_pInput ? (m_pInput->Get() * m_factor + m_bias) : 0.0f;
}

float FloatBiasFactorConnection::Bias() const { return m_bias; }

float FloatBiasFactorConnection::Factor() const { return m_factor; }

// brain::FloatSigmoidFeedForwardNode

FloatSigmoidFeedForwardNode::FloatSigmoidFeedForwardNode() : FeedForwardNode{ } { }

FloatSigmoidFeedForwardNode::FloatSigmoidFeedForwardNode(FloatData* t_pData) : FeedForwardNode{ t_pData } { }

FloatSigmoidFeedForwardNode::FloatSigmoidFeedForwardNode(const FloatSigmoidFeedForwardNode& t_other) : FeedForwardNode{ t_other } { }

FloatSigmoidFeedForwardNode::~FloatSigmoidFeedForwardNode() { }

void FloatSigmoidFeedForwardNode::Update()
{
	float total{ 0.0f };

	for (IPullable<float>* t_input : m_inputs)
	{
		total += t_input->Pull();
	}

	m_pData->Set(Sigmoid(total));
}
