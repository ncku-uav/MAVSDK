// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/calibration/calibration.proto)

#include "calibration/calibration.grpc.pb.h"
#include "plugins/calibration/calibration.h"

#include "mavsdk.h"
#include "lazy_plugin.h"
#include "log.h"
#include <atomic>
#include <cmath>
#include <future>
#include <limits>
#include <memory>
#include <sstream>
#include <vector>

namespace mavsdk {
namespace mavsdk_server {

template<typename Calibration = Calibration, typename LazyPlugin = LazyPlugin<Calibration>>
class CalibrationServiceImpl final : public rpc::calibration::CalibrationService::Service {
public:
    CalibrationServiceImpl(LazyPlugin& lazy_plugin) : _lazy_plugin(lazy_plugin) {}


    template<typename ResponseType>
    void fillResponseWithResult(ResponseType* response, mavsdk::Calibration::Result& result) const
    {
        auto rpc_result = translateToRpcResult(result);

        auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
        rpc_calibration_result->set_result(rpc_result);
        std::stringstream ss;
        ss << result;
        rpc_calibration_result->set_result_str(ss.str());

        response->set_allocated_calibration_result(rpc_calibration_result);
    }



    static rpc::calibration::CalibrationResult::Result translateToRpcResult(const mavsdk::Calibration::Result& result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case mavsdk::Calibration::Result::Unknown:
                return rpc::calibration::CalibrationResult_Result_RESULT_UNKNOWN;
            case mavsdk::Calibration::Result::Success:
                return rpc::calibration::CalibrationResult_Result_RESULT_SUCCESS;
            case mavsdk::Calibration::Result::Next:
                return rpc::calibration::CalibrationResult_Result_RESULT_NEXT;
            case mavsdk::Calibration::Result::Failed:
                return rpc::calibration::CalibrationResult_Result_RESULT_FAILED;
            case mavsdk::Calibration::Result::NoSystem:
                return rpc::calibration::CalibrationResult_Result_RESULT_NO_SYSTEM;
            case mavsdk::Calibration::Result::ConnectionError:
                return rpc::calibration::CalibrationResult_Result_RESULT_CONNECTION_ERROR;
            case mavsdk::Calibration::Result::Busy:
                return rpc::calibration::CalibrationResult_Result_RESULT_BUSY;
            case mavsdk::Calibration::Result::CommandDenied:
                return rpc::calibration::CalibrationResult_Result_RESULT_COMMAND_DENIED;
            case mavsdk::Calibration::Result::Timeout:
                return rpc::calibration::CalibrationResult_Result_RESULT_TIMEOUT;
            case mavsdk::Calibration::Result::Cancelled:
                return rpc::calibration::CalibrationResult_Result_RESULT_CANCELLED;
            case mavsdk::Calibration::Result::FailedArmed:
                return rpc::calibration::CalibrationResult_Result_RESULT_FAILED_ARMED;
        }
    }

    static mavsdk::Calibration::Result translateFromRpcResult(const rpc::calibration::CalibrationResult::Result result)
    {
        switch (result) {
            default:
                LogErr() << "Unknown result enum value: " << static_cast<int>(result);
            // FALLTHROUGH
            case rpc::calibration::CalibrationResult_Result_RESULT_UNKNOWN:
                return mavsdk::Calibration::Result::Unknown;
            case rpc::calibration::CalibrationResult_Result_RESULT_SUCCESS:
                return mavsdk::Calibration::Result::Success;
            case rpc::calibration::CalibrationResult_Result_RESULT_NEXT:
                return mavsdk::Calibration::Result::Next;
            case rpc::calibration::CalibrationResult_Result_RESULT_FAILED:
                return mavsdk::Calibration::Result::Failed;
            case rpc::calibration::CalibrationResult_Result_RESULT_NO_SYSTEM:
                return mavsdk::Calibration::Result::NoSystem;
            case rpc::calibration::CalibrationResult_Result_RESULT_CONNECTION_ERROR:
                return mavsdk::Calibration::Result::ConnectionError;
            case rpc::calibration::CalibrationResult_Result_RESULT_BUSY:
                return mavsdk::Calibration::Result::Busy;
            case rpc::calibration::CalibrationResult_Result_RESULT_COMMAND_DENIED:
                return mavsdk::Calibration::Result::CommandDenied;
            case rpc::calibration::CalibrationResult_Result_RESULT_TIMEOUT:
                return mavsdk::Calibration::Result::Timeout;
            case rpc::calibration::CalibrationResult_Result_RESULT_CANCELLED:
                return mavsdk::Calibration::Result::Cancelled;
            case rpc::calibration::CalibrationResult_Result_RESULT_FAILED_ARMED:
                return mavsdk::Calibration::Result::FailedArmed;
        }
    }






    static std::unique_ptr<rpc::calibration::ProgressData> translateToRpcProgressData(const mavsdk::Calibration::ProgressData &progress_data)
    {
        auto rpc_obj = std::make_unique<rpc::calibration::ProgressData>();


            
        rpc_obj->set_has_progress(progress_data.has_progress);
            
        
            
        rpc_obj->set_progress(progress_data.progress);
            
        
            
        rpc_obj->set_has_status_text(progress_data.has_status_text);
            
        
            
        rpc_obj->set_status_text(progress_data.status_text);
            
        

        return rpc_obj;
    }

    static mavsdk::Calibration::ProgressData translateFromRpcProgressData(const rpc::calibration::ProgressData& progress_data)
    {
        mavsdk::Calibration::ProgressData obj;


            
        obj.has_progress = progress_data.has_progress();
            
        
            
        obj.progress = progress_data.progress();
            
        
            
        obj.has_status_text = progress_data.has_status_text();
            
        
            
        obj.status_text = progress_data.status_text();
            
        
        return obj;
    }



    grpc::Status SubscribeCalibrateGyro(grpc::ServerContext* /* context */, const mavsdk::rpc::calibration::SubscribeCalibrateGyroRequest* /* request */, grpc::ServerWriter<rpc::calibration::CalibrateGyroResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::calibration::CalibrateGyroResponse rpc_response;
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->calibrate_gyro_async(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::Calibration::Result result,const mavsdk::Calibration::ProgressData calibrate_gyro) {

            rpc::calibration::CalibrateGyroResponse rpc_response;
        
            rpc_response.set_allocated_progress_data(translateToRpcProgressData(calibrate_gyro).release());
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
            rpc_calibration_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_calibration_result->set_result_str(ss.str());
            rpc_response.set_allocated_calibration_result(rpc_calibration_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                *is_finished = true;
                unregister_stream_stop_promise(stream_closed_promise);
                stream_closed_promise->set_value();
            }
        });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SubscribeCalibrateAccelerometer(grpc::ServerContext* /* context */, const mavsdk::rpc::calibration::SubscribeCalibrateAccelerometerRequest* /* request */, grpc::ServerWriter<rpc::calibration::CalibrateAccelerometerResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::calibration::CalibrateAccelerometerResponse rpc_response;
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->calibrate_accelerometer_async(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::Calibration::Result result,const mavsdk::Calibration::ProgressData calibrate_accelerometer) {

            rpc::calibration::CalibrateAccelerometerResponse rpc_response;
        
            rpc_response.set_allocated_progress_data(translateToRpcProgressData(calibrate_accelerometer).release());
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
            rpc_calibration_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_calibration_result->set_result_str(ss.str());
            rpc_response.set_allocated_calibration_result(rpc_calibration_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                *is_finished = true;
                unregister_stream_stop_promise(stream_closed_promise);
                stream_closed_promise->set_value();
            }
        });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SubscribeCalibrateMagnetometer(grpc::ServerContext* /* context */, const mavsdk::rpc::calibration::SubscribeCalibrateMagnetometerRequest* /* request */, grpc::ServerWriter<rpc::calibration::CalibrateMagnetometerResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::calibration::CalibrateMagnetometerResponse rpc_response;
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->calibrate_magnetometer_async(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::Calibration::Result result,const mavsdk::Calibration::ProgressData calibrate_magnetometer) {

            rpc::calibration::CalibrateMagnetometerResponse rpc_response;
        
            rpc_response.set_allocated_progress_data(translateToRpcProgressData(calibrate_magnetometer).release());
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
            rpc_calibration_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_calibration_result->set_result_str(ss.str());
            rpc_response.set_allocated_calibration_result(rpc_calibration_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                *is_finished = true;
                unregister_stream_stop_promise(stream_closed_promise);
                stream_closed_promise->set_value();
            }
        });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SubscribeCalibrateLevelHorizon(grpc::ServerContext* /* context */, const mavsdk::rpc::calibration::SubscribeCalibrateLevelHorizonRequest* /* request */, grpc::ServerWriter<rpc::calibration::CalibrateLevelHorizonResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::calibration::CalibrateLevelHorizonResponse rpc_response;
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->calibrate_level_horizon_async(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::Calibration::Result result,const mavsdk::Calibration::ProgressData calibrate_level_horizon) {

            rpc::calibration::CalibrateLevelHorizonResponse rpc_response;
        
            rpc_response.set_allocated_progress_data(translateToRpcProgressData(calibrate_level_horizon).release());
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
            rpc_calibration_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_calibration_result->set_result_str(ss.str());
            rpc_response.set_allocated_calibration_result(rpc_calibration_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                *is_finished = true;
                unregister_stream_stop_promise(stream_closed_promise);
                stream_closed_promise->set_value();
            }
        });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status SubscribeCalibrateGimbalAccelerometer(grpc::ServerContext* /* context */, const mavsdk::rpc::calibration::SubscribeCalibrateGimbalAccelerometerRequest* /* request */, grpc::ServerWriter<rpc::calibration::CalibrateGimbalAccelerometerResponse>* writer) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
                rpc::calibration::CalibrateGimbalAccelerometerResponse rpc_response;
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(&rpc_response, result);
                writer->Write(rpc_response);
            
            return grpc::Status::OK;
        }

        auto stream_closed_promise = std::make_shared<std::promise<void>>();
        auto stream_closed_future = stream_closed_promise->get_future();
        register_stream_stop_promise(stream_closed_promise);

        auto is_finished = std::make_shared<bool>(false);
        auto subscribe_mutex = std::make_shared<std::mutex>();

        _lazy_plugin.maybe_plugin()->calibrate_gimbal_accelerometer_async(
            [this, &writer, &stream_closed_promise, is_finished, subscribe_mutex](mavsdk::Calibration::Result result,const mavsdk::Calibration::ProgressData calibrate_gimbal_accelerometer) {

            rpc::calibration::CalibrateGimbalAccelerometerResponse rpc_response;
        
            rpc_response.set_allocated_progress_data(translateToRpcProgressData(calibrate_gimbal_accelerometer).release());
        

        
            auto rpc_result = translateToRpcResult(result);
            auto* rpc_calibration_result = new rpc::calibration::CalibrationResult();
            rpc_calibration_result->set_result(rpc_result);
            std::stringstream ss;
            ss << result;
            rpc_calibration_result->set_result_str(ss.str());
            rpc_response.set_allocated_calibration_result(rpc_calibration_result);
        

            std::unique_lock<std::mutex> lock(*subscribe_mutex);
            if (!*is_finished && !writer->Write(rpc_response)) {
                
                *is_finished = true;
                unregister_stream_stop_promise(stream_closed_promise);
                stream_closed_promise->set_value();
            }
        });

        stream_closed_future.wait();
        std::unique_lock<std::mutex> lock(*subscribe_mutex);
        *is_finished = true;

        return grpc::Status::OK;
    }

    grpc::Status Cancel(
        grpc::ServerContext* /* context */,
        const rpc::calibration::CancelRequest* /* request */,
        rpc::calibration::CancelResponse* response) override
    {
        if (_lazy_plugin.maybe_plugin() == nullptr) {
            
            if (response != nullptr) {
                auto result = mavsdk::Calibration::Result::NoSystem;
                fillResponseWithResult(response, result);
            }
            
            return grpc::Status::OK;
        }

        
        auto result = _lazy_plugin.maybe_plugin()->cancel();
        

        
        if (response != nullptr) {
            fillResponseWithResult(response, result);
        }
        

        return grpc::Status::OK;
    }


    void stop() {
        _stopped.store(true);
        for (auto& prom : _stream_stop_promises) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        }
    }

private:
    void register_stream_stop_promise(std::weak_ptr<std::promise<void>> prom) {
        // If we have already stopped, set promise immediately and don't add it to list.
        if (_stopped.load()) {
            if (auto handle = prom.lock()) {
                handle->set_value();
            }
        } else {
            _stream_stop_promises.push_back(prom);
        }
    }

    void unregister_stream_stop_promise(std::shared_ptr<std::promise<void>> prom) {
        for (auto it = _stream_stop_promises.begin(); it != _stream_stop_promises.end(); /* ++it */) {
            if (it->lock() == prom) {
                it = _stream_stop_promises.erase(it);
            } else {
                ++it;
            }
        }
    }

    LazyPlugin& _lazy_plugin;
    std::atomic<bool> _stopped{false};
    std::vector<std::weak_ptr<std::promise<void>>> _stream_stop_promises {};
};

} // namespace mavsdk_server
} // namespace mavsdk