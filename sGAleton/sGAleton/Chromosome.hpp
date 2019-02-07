#pragma once

#include <vector>
#include <memory>

class Chromosome
{
public:
	typedef std::shared_ptr<Chromosome> Ptr;

	struct Slice{
		unsigned int top;
		unsigned int bottom;
		unsigned int left;
		unsigned int right;

		inline unsigned int getArea() const{
			return ((bottom-top)*(right-left));
		}
	};

public:
	Chromosome(std::vector<unsigned int> cF, std::vector<unsigned int> cC);

	Chromosome();

	~Chromosome();

	double fitness();

	std::vector<unsigned int> getCortesF() const;

	std::vector<unsigned int> getCortesC() const;
private:
	//std::vector<Gen::Ptr> m_genes;

	bool modifiedSinceLastFitness;
	double lastfitness;
	std::vector<unsigned int> m_cortesF;
	std::vector<unsigned int> m_cortesC;



	int sliceScore(Slice s) const;

};

