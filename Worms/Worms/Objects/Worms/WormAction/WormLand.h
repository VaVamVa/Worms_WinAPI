#pragma once


class WormLand : public WormAction
{
public:
	WormLand(Worm* worm);
	~WormLand();

	void Start(bool isRight) override;
};