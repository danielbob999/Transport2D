#pragma once

class CoreSystem {
private:
public:
	virtual void start() { }
	virtual void update(double delta) { }
	virtual void render(double delta) { }
	virtual void close() { }
};
