#pragma once
#include "../../core/console/Console.h"
#include "../../core/coresystem/CoreSystem.h"
#include "imgui/imgui.h"
#include "box2d/box2d.h"
#include <vector>

class ControlsDisplay : public CoreSystem {
private:
	static ControlsDisplay* s_instance;

	struct DisplayEntry {
		void* parent;
		std::string message;
		std::string actionChar;
		int displayPriority;
	};

	std::vector<DisplayEntry> m_entries;
public:
	ControlsDisplay();
	~ControlsDisplay();

	void start() override;
	void update(double) override;
	void render(double) override;
	void close() override;

	void registerControl(void*, std::string, std::string);

	static ControlsDisplay* getInstance();
};
