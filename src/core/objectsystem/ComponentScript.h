#pragma once
#include <string>

namespace core_objectsystem {
	class ComponentScript {
	private:
		int m_parentId;
	public:
		int getParentId();
		void setParentId(int);

		virtual void start() = 0;
		virtual void update() = 0;
		virtual void close() = 0;
		virtual std::string getTypeString() = 0;
	};
}
