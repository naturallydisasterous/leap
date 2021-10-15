#include <ola/DmxBuffer.h>
#include <ola/Logging.h>
#include <ola/OlaClientWrapper.h>


uint8_t R = 0;
uint8_t G = 0;
uint8_t B = 0;

void onDmx(const ola::client::DMXMetadata& metadata, const ola::DmxBuffer& buffer)
{
  bool changeDetected = false;
  if(R != buffer.Get(0))
    {
      R = buffer.Get(0);
      changeDetected = true;
    }
  if(G != buffer.Get(1))
    {
      G = buffer.Get(1);
      changeDetected = true;
    }
  if(B != buffer.Get(2))
    {
      B = buffer.Get(2);
      changeDetected = true;
    }

  if(changeDetected)
    {
      OLA_WARN
        << (unsigned)R << " "
        << (unsigned)G << " " 
        << (unsigned)B;
    }
}

void onRegisterComplete(const ola::client::Result& result)
{
  if(result.Success())
    {
      OLA_WARN << "Registered";
    }
  else
    {
      OLA_WARN << "Register Failed: " << result.Error();
    }
}

int main(int argc, char* argv[])
{
  ola::InitLogging(ola::OLA_LOG_INFO, ola::OLA_LOG_STDERR);
  ola::client::OlaClientWrapper wrapper;
  if(!wrapper.Setup())
    {
      return 1;
    }

  ola::client::OlaClient* client = wrapper.GetClient();
  client->SetDMXCallback(ola::NewCallback(&onDmx));
  client->RegisterUniverse(0u, ola::client::REGISTER, ola::NewSingleCallback(&onRegisterComplete));

  // Event Loop
  wrapper.GetSelectServer()->Run();

  return 0;
}
