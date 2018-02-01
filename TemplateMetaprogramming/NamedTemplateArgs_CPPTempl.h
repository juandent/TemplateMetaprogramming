#pragma once

#include <iostream>

// to be replaced with real default types!!!
struct DefaultPolicy1 {};
struct DefaultPolicy2 {};
struct DefaultPolicy3 {};
struct DefaultPolicy4 {};




class DefaultPolicies
{
public:
	using P1 = DefaultPolicy1;
	using P2 = DefaultPolicy2;
	using P3 = DefaultPolicy3;
	using P4 = DefaultPolicy4;
};

class DefaultPolicyArgs : public virtual DefaultPolicies
{};

template<typename Policy>
class Policy1_is : public virtual DefaultPolicies
{
public:
	using P1 = Policy;	// overriding type alias
};

template<typename Policy>
class Policy2_is : public virtual DefaultPolicies
{
public:
	using P2 = Policy;	// overriding type alias
};

template<typename Policy>
class Policy3_is : public virtual DefaultPolicies
{
public:
	using P3 = Policy;	// overriding type alias
};

template<typename Policy>
class Policy4_is : public virtual DefaultPolicies
{
public:
	using P4 = Policy;	// overriding type alias
};



template<typename Base, int D>
class Discriminator : public Base
{};

template<typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class PolicySelector : public Discriminator<Setter1, 1>,
	public Discriminator<Setter2, 2>,
	public Discriminator<Setter3, 3>,
	public Discriminator<Setter4, 4>
{};

template<typename PolicySetter1 = DefaultPolicyArgs,
	typename PolicySetter2 = DefaultPolicyArgs,
	typename PolicySetter3 = DefaultPolicyArgs,
	typename PolicySetter4 = DefaultPolicyArgs>
	class BreadSlicer
{
	using Policies = PolicySelector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4>;
	// use Policies::P1, Policies::P2, ... to refer to the different policies

public:
	void print()
	{
		Policies::P3::doPrint();
	}
};


// sample
struct CustomPolicy 
{
	static void doPrint() 
	{
		std::cout << "printing in custom policy" << std::endl;
	}
};

using  overridesDefaultNumber3 = BreadSlicer<Policy3_is<CustomPolicy>>;

void useNamedTemplateArgs()
{
	overridesDefaultNumber3 bs{};

	bs.print();

}

