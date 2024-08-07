/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpResponse.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okraus <okraus@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 10:52:29 by plouda            #+#    #+#             */
/*   Updated: 2024/07/19 16:01:52 by okraus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/HttpResponse.hpp"
#include "../inc/HttpRequest.hpp"

HttpResponse::HttpResponse()
{
	this->statusLine.httpVersion = "HTTP/1.1";
	this->statusLine.statusCode = 200;
	this->statusLine.reasonPhrase = "OK";
	this->headerFields["Server: "] = "webserv/nginx-but-better";
	this->codeDict[100] = "Continue";
	this->codeDict[200] = "OK";
	this->codeDict[201] = "Created";
	this->codeDict[202] = "Accepted";
	this->codeDict[203] = "Non-Authoritative Information";
	this->codeDict[204] = "No Content";
	this->codeDict[205] = "Reset Content";
	this->codeDict[206] = "Partial Content";
	this->codeDict[300] = "Multiple Choices";
	this->codeDict[301] = "Moved Permanently";
	this->codeDict[302] = "Found";
	this->codeDict[303] = "See Other";
	this->codeDict[304] = "Not Modified";
	this->codeDict[305] = "Use Proxy";
	this->codeDict[306] = "Unused";
	this->codeDict[307] = "Temporary Redirect";
	this->codeDict[308] = "Permanent Redirect";
	this->codeDict[400] = "Bad Request";
	this->codeDict[401] = "Unauthorized";
	this->codeDict[402] = "Payment required";
	this->codeDict[403] = "Forbidden";
	this->codeDict[404] = "Not Found";
	this->codeDict[405] = "Method Not Allowed";
	this->codeDict[406] = "Not Acceptable";
	this->codeDict[407] = "Proxy Authentication Required";
	this->codeDict[408] = "Request Timeout";
	this->codeDict[409] = "Conflict";
	this->codeDict[410] = "Gone";
	this->codeDict[411] = "Length Required";
	this->codeDict[412] = "Precondition Failed";
	this->codeDict[413] = "Content Too Large";
	this->codeDict[414] = "URI Too Long";
	this->codeDict[415] = "Unsupported Media Type";
	this->codeDict[416] = "Range Not Satisfiable";
	this->codeDict[417] = "Expectation Failed";
	this->codeDict[418] = "Unused";
	this->codeDict[421] = "Misdirected Request";
	this->codeDict[422] = "Unprocessable Content";
	this->codeDict[426] = "Upgrade Required";
	this->codeDict[500] = "Internal Server Error";
	this->codeDict[501] = "Not Implemented";
	this->codeDict[502] = "Bad Gateway";
	this->codeDict[503] = "Service Unavailable";
	this->codeDict[504] = "Gateway Timeout";
	this->codeDict[505] = "HTTP Version Not Supported";
	this->responseBody = octets_t();
	this->completeResponse = octets_t();
	this->statusLocked = false;
	this->message = octets_t();
	this->messageTooLongForOneSend = false;
	this->cgiStatus = 0;
	this->cgi_pid = 0;
	this->wfd = 0;
	this->rfd = 0;
	this->cgiHeaderFields = stringmap_t();
	this->cgiBody = octets_t();
	return ;
}

// Sun, 06 Nov 1994 08:49:37 GMT 
std::string	getIMFFixdate(void)
{
	time_t		curr_time;
	tm			*curr_tm;
	char		buffer[100];

	std::time(&curr_time);
	curr_tm = std::gmtime(&curr_time);
	std::strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", curr_tm);
	return (std::string(buffer));
}

HttpResponse::HttpResponse(const HttpResponse& refObj)
{
	*this = refObj;
}

HttpResponse& HttpResponse::operator=(const HttpResponse& refObj)
{
	if (this != &refObj)
	{
		statusLine = refObj.statusLine;
		statusDetails = refObj.statusDetails;
		headerFields = refObj.headerFields;
		responseBody = refObj.responseBody;
		completeResponse = refObj.completeResponse;
		codeDict = refObj.codeDict;
		statusLocked = refObj.statusLocked;
		message = refObj.message;
		messageTooLongForOneSend = refObj.messageTooLongForOneSend;
		cgiStatus = refObj.cgiStatus;
		cgi_pid = refObj.cgi_pid;
		wfd = refObj.wfd;
		rfd = refObj.rfd;
		cgiHeaderFields = refObj.cgiHeaderFields;
		cgiBody = refObj.cgiBody;
	}
	return (*this);
}

HttpResponse::~HttpResponse()
{
	return ;
}

const statusLine_t	&HttpResponse::getStatusLine() const
{
	return (this->statusLine);
}

const unsigned short&	HttpResponse::getStatusCode() const
{
	return (this->statusLine.statusCode);
}

const bool &HttpResponse::getStatusLocked() const
{
	return (this->statusLocked);
}

// overrides updateStatus()
void	HttpResponse::setStatusCode(unsigned short code)
{
	this->statusLine.statusCode = code;
}

void HttpResponse::updateStatus(unsigned short code, const char* details)
{
	if (!this->statusLocked)
	{
		this->statusLine.statusCode = code;
		this->statusDetails = details;
	}
	this->statusLocked = true;
}

void HttpResponse::setStatusLineAndDetails(const statusLine_t &incStatusLine, const std::string &details)
{
	this->statusLine.httpVersion = incStatusLine.httpVersion;
	this->statusLine.statusCode = incStatusLine.statusCode;
	this->statusLine.reasonPhrase = this->codeDict[incStatusLine.statusCode];
	this->statusDetails = details;
}

void	HttpResponse::lockStatusCode()
{
	this->statusLocked = true;
}

// needs different Content-Type
// needs proper allowed methods handling
void	HttpResponse::buildResponseHeaders(const HttpRequest& request)
{
	size_t		contentLength = this->responseBody.size();
	std::string	date = getIMFFixdate();
	std::string	type("text/html; charset=utf-8");
	this->headerFields["Content-Length: "] = itoa(contentLength);
	this->headerFields["Date: "] = date;
	this->headerFields["Content-Type: "] = type;
	if (request.getConnectionStatus() == CLOSE)
		this->headerFields["Connection: "] = "close";
	else
	{
		this->headerFields["Connection: "] = "keep-alive";
		this->headerFields["Keep-Alive: "] = std::string("timeout=" + itoa(CONNECTION_TIMEOUT));
	}
	if (this->statusLine.statusCode >= 300 && this->statusLine.statusCode <= 308)
	{
		if (this->statusDetails == "Trying to access a directory")
			this->headerFields["Location: "] = request.getAbsolutePath() + "/";
		else
			this->headerFields["Location: "] = request.getLocation().getReturnURLOrBody();
	}
	if (this->statusLine.statusCode == 405)
	{
		std::string	methods;
		std::set<std::string>::const_iterator it = request.getAllowedMethods().begin();
		while (it != request.getAllowedMethods().end())
		{
			methods.append(*it);
			if (++it != request.getAllowedMethods().end())
				methods.append(", ");
		}
		this->headerFields["Allow: "] = methods;
	}
	if (this->statusLine.statusCode == 426)
	{
		this->headerFields["Connection: "].append(", Upgrade");
		this->headerFields["Upgrade: "] = "HTTP/1.1";
	}
	for (stringmap_t::iterator it = this->headerFields.begin() ; it != this->headerFields.end() ; it++)
		it->second.append(CRLF);
}

void	HttpResponse::readErrorPage(const Location &location)
{
	const std::map<unsigned short, std::string> &errorPages = location.getErrorPages();
	std::ifstream											errorPageFile;
	std::stringstream										buff;
	std::map<unsigned short, std::string>::const_iterator	it;
	std::stringstream										ss;
	
	it = errorPages.find(this->statusLine.statusCode);
	if (it != errorPages.end())
	{
		errorPageFile.open(it->second.c_str());
		if (errorPageFile)
		{
			buff << errorPageFile.rdbuf();
			this->responseBody = convertStringToOctets(buff.str());
			//std::cout << CLR2 << "Response body: " << this->responseBody << RESET << std::endl;
		}
	}
	ss << "<html>\r\n"
	   << "<head><title>" << this->statusLine.statusCode << " " << this->statusLine.reasonPhrase << "</title></head>\r\n"
	   << "<body>\r\n"
	   << "<center><h1>" << this->statusLine.statusCode << " " << this->statusLine.reasonPhrase << "</h1></center>\r\n"
	   << "<center><h2>" << this->statusDetails << "</h2></center>\r\n"
	   << "</html>\r\n";
	this->responseBody = convertStringToOctets(ss.str());
	//std::cout << CLR2 << "Response body: " << this->responseBody << RESET << std::endl;
}

void HttpResponse::readRequestedFile(const std::string &targetResource)
{
	//std::cout << CLR3 << targetResource << RESET << std::endl;
	std::ifstream	stream(targetResource.c_str(), std::ios::binary);
	octets_t		contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
	this->responseBody.insert(this->responseBody.end(), contents.begin(), contents.end());
}

void	HttpResponse::buildCompleteResponse(void)
{
	octets_t	httpVersion(convertStringToOctets(this->statusLine.httpVersion));
	octets_t	statusCode(convertStringToOctets(itoa(this->statusLine.statusCode)));
	octets_t	reasonPhrase(convertStringToOctets(this->statusLine.reasonPhrase));
	octets_t	delimiter(convertStringToOctets(CRLF));
	this->completeResponse.insert(this->completeResponse.end(), httpVersion.begin(), httpVersion.end());
	this->completeResponse.push_back(' ');
	this->completeResponse.insert(this->completeResponse.end(), statusCode.begin(), statusCode.end());
	this->completeResponse.push_back(' ');
	this->completeResponse.insert(this->completeResponse.end(), reasonPhrase.begin(), reasonPhrase.end());
	this->completeResponse.insert(this->completeResponse.end(), delimiter.begin(), delimiter.end());

	for (stringmap_t::iterator it = this->headerFields.begin() ; it != this->headerFields.end() ; it++)
	{
		this->completeResponse.insert(this->completeResponse.end(), it->first.begin(), it->first.end());
		this->completeResponse.insert(this->completeResponse.end(), it->second.begin(), it->second.end());
	}
	this->completeResponse.insert(this->completeResponse.end(), delimiter.begin(), delimiter.end()); // insert extra CRLF

	if (this->responseBody.size() > 0)
		this->completeResponse.insert(this->completeResponse.end(), this->responseBody.begin(), this->responseBody.end());
}

void	HttpResponse::readDirectoryListing(const std::string& targetResource)
{
	std::stringstream		body;
	std::set<std::string>	strings;
	DIR*					dirPtr;
	dirPtr = opendir(targetResource.c_str());
	body << "<html>\r\n"
		<< "<head><title>" << "Index of " << targetResource << "</title></head>\r\n"
		<< "<body>\r\n"
		<< "<h1>" << "Index of " << targetResource << "</h1>\r\n"
		<< "<hr><pre>\r\n";
	body << "<h2> 🏠 <a href=\"../\">"
		<< "Parent Directory"
		<< "</a></h2>";
	body << "<h2>"
		<< "      Name              "
		<< "    Date Modified       "
		<< "Size "
		<< "</h2>";
	for (dirent* dir = readdir(dirPtr); dir != NULL; dir = readdir(dirPtr))
	{
		std::stringstream	tempstream;
		std::string	path = targetResource + dir->d_name;
		struct stat	fileCheckBuff;
		if (stat(path.c_str(), &fileCheckBuff) < 0)
			std::cout << errno << " "<< path << std::endl;
		#ifdef __APPLE__
			tm *curr_tm = std::gmtime(&(fileCheckBuff.st_mtimespec.tv_sec));
		#endif
		#ifdef __linux__
			tm *curr_tm = std::gmtime(&(fileCheckBuff.st_mtim.tv_sec));
		#endif
		char time[100];
		std::strftime(time, 100, "%a, %d %b %Y %H:%M:%S GMT", curr_tm);
		std::string	dname = dir->d_name;
		if (dname.size() > 28)
			dname = dname.substr(0, 25) + "...";
		if (dir->d_type == DT_DIR)
		{
			tempstream << " 📁 <a href=\""
			<< dir->d_name
			<< "/\">"
			<< dname
			<< "/"
			<< "</a>"
			<< std::left << std::setw(30 - dname.size()) << " "
			<< " "
			<< std::left << std::setw(30) << time
			<< " "
			<< std::right << std::setw(10) << "- "
			<< "\r\n";
		}
		else if (dir->d_type == DT_REG)
		{
			tempstream << " 📄 <a href=\""
			<< dir->d_name
			<< "\">"
			<< dname
			<< "" << "</a>"
			<< std::left << std::setw(31 - dname.size()) << " "
			<< " "
			<< std::left << std::setw(30) << time
			<< " ";
			double				size;
			std::string			strsize;
			size = fileCheckBuff.st_size;
			if (size > 1024ULL * 1024ULL * 1024ULL * 1024ULL)
			{
				size /= 1024ULL * 1024ULL * 1024ULL * 1024ULL;
				strsize = " TB";
				tempstream << std::right << std::setw(7) << std::fixed << std::setprecision(1)
				<< size << strsize
				<< "\r\n";
			}
			else if (size > 1024ULL * 1024ULL * 1024ULL)
			{
				size /= 1024ULL * 1024ULL * 1024ULL;
				strsize = " GB";
				tempstream << std::right << std::setw(7) << std::fixed << std::setprecision(1)
				<< size << strsize
				<< "\r\n";
			}
			else if (size > 1024ULL * 1024ULL)
			{
				size /= 1024ULL * 1024ULL;
				strsize = " MB";
				tempstream << std::right << std::setw(7) << std::fixed << std::setprecision(1)
				<< size << strsize
				<< "\r\n";
			}
			else if (size > 1024ULL)
			{
				size /= 1024ULL;
				strsize = " kB";
				tempstream << std::right << std::setw(7) << std::fixed << std::setprecision(1)
				<< size << strsize
				<< "\r\n";
			}
			else
			{
				strsize = "  B";
				tempstream << std::right << std::setw(7)
				<< size << strsize
				<< "\r\n";
			}
		}
		strings.insert(tempstream.str());
	}
	std::set<std::string>::iterator it;
	for (it = strings.begin(); it != strings.end(); ++it) {
		if ((*it).find(" 📁 <a href=\"./\">") != std::string::npos
			|| (*it).find(" 📁 <a href=\"../\">") != std::string::npos)
			continue ;
		body << *it;
	}
	body << "</pre><hr></body>\r\n";
	body << "</html>\r\n";
	this->responseBody = convertStringToOctets(body.str());
	closedir(dirPtr);
}
void	HttpResponse::readReturnDirective(const Location &location)
{
	this->responseBody = convertStringToOctets(location.getReturnURLOrBody());
}

const octets_t		HttpResponse::prepareResponse(HttpRequest& request)
{
	if (request.getHasExpect())
		return (convertStringToOctets("HTTP/1.1 100 Continue"));
	else
	{
		if (request.getLocation().getIsCgi())
		{
			//cgi stuff
			// std::cout << CLR2 << "CGI STUFF"<< RESET << std::endl;
			// std::string str(this->cgiBody.begin(), this->cgiBody.end());
			// std::cout << str << std::endl;
			return (this->cgiBody);
		}
		std::cout << CLR1 << this->statusLine.statusCode << RESET << std::endl;
		if (codeDict.find(this->statusLine.statusCode) == codeDict.end())
			this->codeDict[this->statusLine.statusCode] = "Undefined";
		this->statusLine.reasonPhrase = this->codeDict[this->statusLine.statusCode];
		if (this->statusLine.statusCode == 200 && request.getTargetIsDirectory())
			request.response.readDirectoryListing(request.getTargetResource());
		else if (this->statusLine.statusCode == 200)
			request.response.readRequestedFile(request.getTargetResource());
		else if (request.getLocation().getIsRedirect() && (this->statusLine.statusCode < 300 || this->statusLine.statusCode > 308))
			request.response.readReturnDirective(request.getLocation());
		else
			request.response.readErrorPage(request.getLocation());
		request.response.buildResponseHeaders(request);
		request.response.buildCompleteResponse();
		octets_t message = request.response.getCompleteResponse();
		return (message);
	}
}

const octets_t &HttpResponse::getCompleteResponse() const
{
	return (this->completeResponse);
}

const octets_t&	HttpResponse::getMessage() const
{
	return(this->message);

}

void	HttpResponse::setMessage(const octets_t& message)
{
	this->message = message;
}

void	HttpResponse::eraseRangeMessage(size_t start, size_t end)
{
	if (start <= end && end <= this->message.size())
		this->message.erase(this->message.begin() + start, this->message.begin() + end);
}

bool	HttpResponse::getMessageTooLongForOneSend() const
{
	return (this->messageTooLongForOneSend);
}

void	HttpResponse::setMessageTooLongForOneSend(bool value)
{
	this->messageTooLongForOneSend = value;
}

int	HttpResponse::getCgiStatus(void)
{
	return(this->cgiStatus);
}

int	HttpResponse::getCgiPid(void)
{
	return(this->cgi_pid);
}

int	HttpResponse::getWfd(void)
{
	return(this->wfd);
}

int	HttpResponse::getRfd(void)
{
	return(this->rfd);
}

stringmap_t	HttpResponse::getCgiHeaderFields(void)
{
	return(this->cgiHeaderFields);
}

octets_t&	HttpResponse::getCgiBody(void)
{
	return(this->cgiBody);
}

void	HttpResponse::setCgiStatus(int status)
{
	this->cgiStatus = status;
}

void	HttpResponse::setCgiPid(int pid)
{
	this->cgi_pid = pid;
}

void	HttpResponse::setWfd(int fd)
{
	this->wfd = fd;
}

void	HttpResponse::setRfd(int fd)
{
	this->rfd = fd;
}
