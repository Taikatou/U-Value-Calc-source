#include "IwDebug.h"
#include <deque>
#include <string>

#define MAX_LOG 10

void dump(int &y, const char* tmp)
{
	static char buffer[1024];
	sprintf(buffer, "`xff0000%s", tmp);
	y += 20;
	s3eDebugPrint(50, y, buffer, 1);
}

class CEventLog
{
public:
	CEventLog()
	{
		m_Log.push_back("--- Event Log ---");
	}

	void Log(std::string eventstr)
	{
		IwTrace(S3EAMAZONADS_EXAMPLE, (eventstr.c_str()));

		m_Log.push_back(eventstr);
		if (m_Log.size() > MAX_LOG)
			m_Log.pop_front();
	}

	void Display(int y)
	{
		std::deque<std::string>::iterator it = m_Log.begin();
		int i = 0;
		while (it != m_Log.end() && i < MAX_LOG)
		{
			dump(y, it->c_str());
			i++;
			it++;
		}
	}
private:
	std::deque<std::string> m_Log;
};
