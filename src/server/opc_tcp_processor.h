/// @author Alexander Rykovanov 2013
/// @email rykovanov.as@gmail.com
/// @brief OpcUa binary protocol connection processor.
/// @license GNU LGPL
///
/// Distributed under the GNU LGPL License
/// (See accompanying file LICENSE or copy at
/// http://www.gnu.org/licenses/lgpl.html)
///

#include <opc/ua/protocol/binary/common.h>
#include <opc/ua/protocol/binary/stream.h>
#include <opc/ua/server.h>

#include <chrono>
#include <list>
#include <mutex>
#include <queue>

namespace OpcUa
{
  namespace UaServer
  {

    class OpcTcpMessages
    {
    public:
      OpcTcpMessages(std::shared_ptr<OpcUa::Remote::Server> computer, OpcUa::OutputChannel& outputChannel, bool debug);

      void ProcessMessage(Binary::MessageType msgType, Binary::IStreamBinary& iStream);
      void SendPublishResponse(OpcUa::OutputChannel& clientChannel);
      double GetNextSleepPeriod();

    private:
      void HelloClient(Binary::IStreamBinary& istream, Binary::OStreamBinary& ostream);
      void OpenChannel(Binary::IStreamBinary& istream, Binary::OStreamBinary& ostream);
      void CloseChannel(Binary::IStreamBinary& istream);
      void ProcessRequest(Binary::IStreamBinary& istream, Binary::OStreamBinary& ostream);
      void FillResponseHeader(const RequestHeader& requestHeader, ResponseHeader& responseHeader);
      void DeleteSubscriptions(const std::vector<IntegerID>& ids);
      void SendPublishResponse();

    private:
      std::mutex ProcessMutex;
      std::shared_ptr<OpcUa::Remote::Server> Server;
      OpcUa::Binary::OStreamBinary OutputStream;
      bool Debug;
      uint32_t ChannelID;
      uint32_t TokenID;
      NodeID SessionID;
      NodeID AuthenticationToken;
      uint32_t SequenceNb;

      struct SubscriptionBinaryData
      {
        IntegerID SubscriptionID;
        std::chrono::duration<double> period;
        std::chrono::duration<double> last_check;
      };

      struct PublishRequestElement
      {
        Binary::SequenceHeader sequence;
        RequestHeader requestHeader;
        Binary::SymmetricAlgorithmHeader algorithmHeader;
      };

      std::list<SubscriptionBinaryData> Subscriptions; //Keep a list of subscriptions to query internal server at correct rate
      std::queue<PublishRequestElement> PublishRequestQueue; //Keep track of request data to answer them when we have data and
    };


  } // namespace UaServer
} // namespace OpcUa
