#include "ResponseDelete.hpp"


namespace hhpp
{

	ResponseDelete::ResponseDelete(Location *location) : Response(), _location(location)
	{
		if (!_location->exists())
		{
			setStatus(404);
			setBody(getStatusMessage());
			setContentType("text/html");
		}
		else
		{

			if (_location->isFolder())
			{
				setStatus(406);
				setBody(getStatusMessage());
				setContentType("text/html");
			}
			else
			{
				if (_location->removeFile())
				{
					setStatus(204);
				}
				else
				{
					setStatus(500);
					setBody(getStatusMessage());
					setContentType("text/html");
				}
			}
		}
	}

	ResponseDelete::~ResponseDelete()
	{
	}

} // namespace hhpp
