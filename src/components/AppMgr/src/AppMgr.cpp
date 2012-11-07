#include "AppMgr/AppMgr.h"
#include "JSONHandler/JSONHandler.h"
#include "AppMgr/AppFactory.h"
#include "AppMgr/AppMgrCore.h"
#include "AppMgr/AppMgrRegistry.h"
#include "LoggerHelper.hpp"
#include "JSONHandler/ALRPCMessage.h"

namespace NsAppManager
{
log4cplus::Logger AppMgr::mLogger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("AppMgr"));

AppMgr& AppMgr::getInstance( )
{
	static AppMgr appMgr;
	return appMgr;
}

AppMgr::AppMgr()
    :mAppMgrRegistry(AppMgrRegistry::getInstance())
	,mAppMgrCore(AppMgrCore::getInstance())
	,mAppFactory(AppFactory::getInstance())
	,mJSONHandler(0)
{
	LOG4CPLUS_INFO_EXT(mLogger, " AppMgr constructed!");
}

AppMgr::~AppMgr()
{
    LOG4CPLUS_INFO_EXT(mLogger, " AppMgr destructed!");
}

AppMgr::AppMgr(const AppMgr &)
    :mAppMgrRegistry(AppMgrRegistry::getInstance())
    ,mAppMgrCore(AppMgrCore::getInstance())
    ,mAppFactory(AppFactory::getInstance())
    ,mJSONHandler(0)
{
}

void AppMgr::setJsonHandler(JSONHandler* handler)
{
    if(!handler)
    {
        LOG4CPLUS_ERROR_EXT(mLogger, " Setting null handler!");
        return;
    }
    mAppMgrCore.setJsonHandler( handler );
}

void AppMgr::setJsonRPC2Handler(JSONRPC2Handler *handler)
{
    if(!handler)
    {
        LOG4CPLUS_ERROR_EXT(mLogger, " Setting null handler!");
        return;
    }
    mAppMgrCore.setJsonRPC2Handler( handler );
}

void AppMgr::onMessageReceivedCallback(ALRPCMessage * message , unsigned char sessionID)
{
    if(!message)
    {
        LOG4CPLUS_ERROR_EXT(mLogger, " Calling a function with null command! Session id "<<sessionID);
        return;
    }
    LOG4CPLUS_INFO_EXT(mLogger, " Message "<<message->getMethodId()<<" received from mobile side");
    mAppMgrCore.pushMobileRPCMessage( message, sessionID );
}

void AppMgr::onCommandReceivedCallback(RPC2Communication::RPC2Command *command)
{
    if(!command)
    {
        LOG4CPLUS_ERROR_EXT(mLogger, " Calling a function with null command!");
        return;
    }
    LOG4CPLUS_INFO_EXT(mLogger, " Message "<<command->getMethod()<<" received from HMI side");
    mAppMgrCore.pushRPC2CommunicationMessage(command);
}

/**
 * \brief pure virtual method to process response.
 * \param method method name which has been called.
 * \param root JSON message.
 */
void AppMgr::processResponse(std::string method, Json::Value& root)
{
	LOG4CPLUS_INFO_EXT(mLogger, " Processing a response to "<<method);
    //mAppLinkInterface.processResponse(method, root);
}

/**
 * \brief pure virtual method to process request.
 * \param root JSON message.
 */
void AppMgr::processRequest(Json::Value& root)
{
	LOG4CPLUS_INFO_EXT(mLogger, " Processing a request");
    //mAppLinkInterface.processRequest(root);
}

/**
 * \brief Process notification message.
 * \brief Notify subscribers about property change.
 * expected notification format example:
 * \code
 * {"jsonrpc": "2.0", "method": "<ComponentName>.<NotificationName>", "params": <list of params>}
 * \endcode
 * \param root JSON message.
 */
void AppMgr::processNotification(Json::Value& root)
{
	LOG4CPLUS_INFO_EXT(mLogger, " Processing a notification");
    //mAppLinkInterface.processNotification(root);
}

void AppMgr::startAppMgr()
{
    LOG4CPLUS_INFO_EXT(mLogger, " Starting AppMgr...");
    //mAppLinkInterface.registerController();
    //mAppLinkInterface.prepareComponent();
    LOG4CPLUS_INFO_EXT(mLogger, " Started AppMgr!");
}

}
