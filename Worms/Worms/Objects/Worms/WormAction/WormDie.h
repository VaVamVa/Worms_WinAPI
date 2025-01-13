#pragma once

class WormDie : public WormAction
{
public:
	WormDie(Worm* worm);
	~WormDie();

	void Start(bool isRight) override;
};