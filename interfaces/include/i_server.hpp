#ifndef I_SERVER
#define I_SERVER

class IServer
{
public:
    virtual ~IServer() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // I_SERVER