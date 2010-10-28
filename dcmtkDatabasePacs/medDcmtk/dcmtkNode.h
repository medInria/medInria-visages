#ifndef DCMTKNODE_H
#define DCMTKNODE_H

// inc
#include <iostream>

#include "dcmtkResultDataset.h"


class dcmtkNode
{
public:

    inline void setTitle(std::string title) {
        m_title = title;
    }

    inline void setIp(std::string ip) {
        m_ip = ip;
    }
    
    inline void setPort(unsigned int port) {
        m_port = port;
    }

    inline std::string title(void) {
        return m_title;
    }

    inline std::string ip(void) {
        return m_ip;
    }
    
    inline unsigned int port(void) {
        return m_port;
    }

    dcmtkContainer<dcmtkResultDataset*>* getResultDatasetContainer(void);

protected:
    dcmtkContainer<dcmtkResultDataset*>  m_dsContainer;

protected:
    std::string  m_title;
    std::string  m_ip;
    unsigned int m_port;
};

#endif //DCMTKNODE_H