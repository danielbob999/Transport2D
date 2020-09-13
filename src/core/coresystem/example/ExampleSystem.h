#pragma once
#include "../CoreSystem.h"

class ExampleSystem : public CoreSystem {
private:
	static ExampleSystem* s_instance;
public:
	ExampleSystem();
	~ExampleSystem();

	void start() override;
	void update(double) override;
	void render(double) override;
	void close() override;

	static ExampleSystem* getInstance();
};
