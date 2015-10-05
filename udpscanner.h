#pragma once
#include <unordered_map>
#include "stdafx.h"
#include "portscanner.h"

/*!
 * Represents scan data for the UDP scanner.
 */
struct UdpScanData
{

	/*!
	 * "Connected" socket.
	 */
	SOCKET socket;

};

/*!
 * Represents a payload.
 */
struct Payload
{

	/*!
	 * Data in the payload.
	 */
	char* data = nullptr;

	/*!
	 * Length of the data.
	 */
	int datlen = 0;

};

/*!
 * Implements an UDP port scanner.
 * 
 * This will try to initiate the three-way handshake with all the requested services.
 * It is not a stealthy method, and does not include any trickery to bypass firewalls.
 */
class UdpScanner : public PortScanner
{
public:
	
	/*!
	 * Number of milliseconds to wait for response.
	 */
	unsigned long timeout = 1000;

	/*!
	 * Map of well-known ports and their example payload.
	 */
	static std::unordered_map<unsigned short, struct Payload*> payloads;

	/*!
	 * Scans a service to determine aliveness.
	 * 
	 * \param service Service.
	 */
	void Scan(Service* service) override;

	/*!
	 * Scans a list of services to determine aliveness.
	 * 
	 * \param services List of services.
	 */
	void Scan(Services* services) override;

	/*!
	 * Frees up the resources allocated during the lifetime of this instance.
	 */
	~UdpScanner() override;

private:

	/*!
	 * Sends a datagram to each requested service, with crafted packet, when available.
	 *
	 * \param service Service.
	 */
	void initSocket(Service* service);

	/*!
	 * Receives the responses.
	 *
	 * \param service Service.
	 * \param last Whether this is the last iteration.
	 */
	void pollSocket(Service* service, bool last = false);

	/*!
	 * Loads the payload database from external file.
	 */
	void loadPayloads();

};
