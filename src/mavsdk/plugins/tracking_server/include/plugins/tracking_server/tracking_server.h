// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/main/protos/tracking_server/tracking_server.proto)

#pragma once

#include <array>
#include <cmath>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "mavsdk/plugin_base.h"

namespace mavsdk {

class System;
class TrackingServerImpl;

/**
 * @brief API for an onboard image tracking software.
 */
class TrackingServer : public PluginBase {
public:
    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto tracking_server = TrackingServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit TrackingServer(System& system); // deprecated

    /**
     * @brief Constructor. Creates the plugin for a specific System.
     *
     * The plugin is typically created as shown below:
     *
     *     ```cpp
     *     auto tracking_server = TrackingServer(system);
     *     ```
     *
     * @param system The specific system associated with this plugin.
     */
    explicit TrackingServer(std::shared_ptr<System> system); // new

    /**
     * @brief Destructor (internal use only).
     */
    ~TrackingServer();


    /**
     * @brief Answer to respond to an incoming command
     */
    enum class CommandAnswer {
        Accepted, /**< @brief Command accepted. */
        TemporarilyRejected, /**< @brief Command temporarily rejected. */
        Denied, /**< @brief Command denied. */
        Unsupported, /**< @brief Command unsupported. */
        Failed, /**< @brief Command failed. */
    };

    /**
     * @brief Stream operator to print information about a `TrackingServer::CommandAnswer`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, TrackingServer::CommandAnswer const& command_answer);




    /**
     * @brief Point description type
     */
    struct TrackPoint {
        
        float point_x{}; /**< @brief Point to track x value (normalized 0..1, 0 is left, 1 is right). */
        float point_y{}; /**< @brief Point to track y value (normalized 0..1, 0 is top, 1 is bottom). */
        float radius{}; /**< @brief Point to track y value (normalized 0..1, 0 is top, 1 is bottom). */
    };

    /**
     * @brief Equal operator to compare two `TrackingServer::TrackPoint` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const TrackingServer::TrackPoint& lhs, const TrackingServer::TrackPoint& rhs);

    /**
     * @brief Stream operator to print information about a `TrackingServer::TrackPoint`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, TrackingServer::TrackPoint const& track_point);




    /**
     * @brief Rectangle description type
     */
    struct TrackRectangle {
        
        float top_left_corner_x{}; /**< @brief Top left corner of rectangle x value (normalized 0..1, 0 is left, 1 is right). */
        float top_left_corner_y{}; /**< @brief Top left corner of rectangle y value (normalized 0..1, 0 is top, 1 is bottom). */
        float bottom_right_corner_x{}; /**< @brief Bottom right corner of rectangle x value (normalized 0..1, 0 is left, 1 is right). */
        float bottom_right_corner_y{}; /**< @brief Bottom right corner of rectangle y value (normalized 0..1, 0 is top, 1 is bottom). */
    };

    /**
     * @brief Equal operator to compare two `TrackingServer::TrackRectangle` objects.
     *
     * @return `true` if items are equal.
     */
    friend bool operator==(const TrackingServer::TrackRectangle& lhs, const TrackingServer::TrackRectangle& rhs);

    /**
     * @brief Stream operator to print information about a `TrackingServer::TrackRectangle`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, TrackingServer::TrackRectangle const& track_rectangle);





    /**
     * @brief Possible results returned for tracking_server requests.
     */
    enum class Result {
        Unknown, /**< @brief Unknown result. */
        Success, /**< @brief Request succeeded. */
        NoSystem, /**< @brief No system is connected. */
        ConnectionError, /**< @brief Connection error. */
    };

    /**
     * @brief Stream operator to print information about a `TrackingServer::Result`.
     *
     * @return A reference to the stream.
     */
    friend std::ostream& operator<<(std::ostream& str, TrackingServer::Result const& result);



    /**
     * @brief Callback type for asynchronous TrackingServer calls.
     */
    using ResultCallback = std::function<void(Result)>;






    /**
     * @brief Set/update the current point tracking status.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    void set_tracking_point_status(TrackPoint tracked_point) const;






    /**
     * @brief Set/update the current rectangle tracking status.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    void set_tracking_rectangle_status(TrackRectangle tracked_rectangle) const;






    /**
     * @brief Set the current tracking status to off.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    void set_tracking_off_status() const;




        
    /**
    * @brief Callback type for subscribe_tracking_point_command.
    */
        
    using TrackingPointCommandCallback = std::function<void(TrackPoint)>;

    /**
     * @brief Subscribe to incoming tracking point command.
     */
    void subscribe_tracking_point_command(TrackingPointCommandCallback callback);






        
    /**
    * @brief Callback type for subscribe_tracking_rectangle_command.
    */
        
    using TrackingRectangleCommandCallback = std::function<void(TrackRectangle)>;

    /**
     * @brief Subscribe to incoming tracking rectangle command.
     */
    void subscribe_tracking_rectangle_command(TrackingRectangleCommandCallback callback);






        
    /**
    * @brief Callback type for subscribe_tracking_off_command.
    */
        
    using TrackingOffCommandCallback = std::function<void(int32_t)>;

    /**
     * @brief Subscribe to incoming tracking off command.
     */
    void subscribe_tracking_off_command(TrackingOffCommandCallback callback);








    /**
     * @brief Respond to an incoming tracking point command.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result respond_tracking_point_command(CommandAnswer command_answer) const;






    /**
     * @brief Respond to an incoming tracking rectangle command.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result respond_tracking_rectangle_command(CommandAnswer command_answer) const;






    /**
     * @brief Respond to an incoming tracking off command.
     *
     * This function is blocking.
     *
     * @return Result of request.
     */
    Result respond_tracking_off_command(CommandAnswer command_answer) const;




    /**
     * @brief Copy constructor.
     */
    TrackingServer(const TrackingServer& other);

    /**
     * @brief Equality operator (object is not copyable).
     */
    const TrackingServer& operator=(const TrackingServer&) = delete;

private:
    /** @private Underlying implementation, set at instantiation */
    std::unique_ptr<TrackingServerImpl> _impl;
};

} // namespace mavsdk