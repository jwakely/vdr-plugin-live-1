#ifndef VDR_LIVE_TOOLS_H
#define VDR_LIVE_TOOLS_H

#include <ctime>
#include <string>
#include <vector>
#include <vdr/thread.h>

namespace vdrlive {

std::string FormatDateTime( char const* format, time_t time );
std::string StringReplace( std::string const& text, std::string const& substring, std::string const& replacement );
std::vector< std::string > StringSplit( std::string const& text, char delimiter );

class ReadLock
{
public:
	ReadLock( cRwLock& lock, int timeout = 100 ): m_lock( lock ), m_locked( false ) { if ( m_lock.Lock( false, timeout ) ) m_locked = true; }
	~ReadLock() { if ( m_locked ) m_lock.Unlock(); }

	operator bool() { return m_locked; }
	bool operator!() { return !m_locked; }

private:
	ReadLock( ReadLock const& );

	cRwLock& m_lock;
	bool m_locked;
};

} // namespace vdrlive

#endif // VDR_LIVE_TOOLS_H