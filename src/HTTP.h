///
/// \author Adam Wegrzynek
///

#ifndef INFLUXDATA_TRANSPORTS_HTTP_H
#define INFLUXDATA_TRANSPORTS_HTTP_H

#include "Transport.h"
#include <curl/curl.h>
#include <memory>
#include <string>

namespace influxdb::transports
{

/// \brief HTTP transport
class HTTP : public Transport
{
  public:
    /// Constructor
    HTTP(const std::string& url);

    /// Default destructor
    ~HTTP();

    /// Sends point via HTTP POST
    ///  \throw InfluxDBException	when CURL fails on POSTing or response code != 200
    void send(std::string&& post) override;

    /// Queries database
    /// \throw InfluxDBException	when CURL GET fails
    std::string query(const std::string& query) override;

    /// Creates database used at url if it does not exists
    /// \throw InfluxDBException	when CURL POST fails
    void createDatabase();

    /// Enable Basic Auth
    /// \param auth <username>:<password>
    void enableBasicAuth(const std::string& auth);

    /// Enable SSL
    void enableSsl();

    /// Get the database name managed by this transport
    std::string databaseName() const;

    /// Get the influx service url which transport connects to
    std::string influxDbServiceUrl() const;

  private:

    /// Obtain InfluxDB service url from the url passed
    void obtainInfluxServiceUrl(const std::string& url);

    /// Obtain database name from the url passed
    void obtainDatabaseName(const std::string& url);

    /// Initilizes CURL for writting and common options
    /// \throw InfluxDBException	if database (?db=) not specified
    void initCurl(const std::string& url);

    /// Initializes CURL for reading
    void initCurlRead(const std::string& url);

    /// CURL pointer configured for writting points
    CURL* writeHandle;

    /// CURL pointer configured for querying
    CURL* readHandle;

    /// InfluxDB read URL
    std::string mReadUrl;

    /// InfluxDB service URL
    std::string mInfluxDbServiceUrl;

    /// Database name used
    std::string mDatabaseName;
};

} // namespace influxdb

#endif // INFLUXDATA_TRANSPORTS_HTTP_H
