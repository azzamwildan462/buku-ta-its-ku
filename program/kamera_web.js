// Subscribe to frame
$scope.frame_field =
  "http://" +
  window.location.hostname +
  ":9901" +
  "/stream?topic=" +
  $scope.ns +
  "/vision_field_thresh_main&type=ros_compressed";

// Get cam offset
$scope.req_cam_offset = new ROSLIB.ServiceRequest({});

$scope.ser_cam_offset = new ROSLIB.Service({
  ros: $scope.ros,
  name: "cam_offset",
  serviceType: "iris_msgs/cam_offset",
});

$scope.ser_cam_offset.callService($scope.req_cam_offset, (result) => {
  x_offset_frame = result.data[0];
  y_offset_frame = result.data[1];
});

$scope.get_x_y_data = function () {
  if (1) {
    $(document).ready(function () {
      $("#get_x_y").on("click", function (event) {
        var offset = findPos(document.getElementById("get_x_y"));
        //=============================================================
        var x = event.clientX - offset.X + window.pageXOffset;
        var y = event.clientY - offset.Y + window.pageYOffset;

        var $img = $(this);
        var x_frame = ((this.naturalWidth / $img.width()) * x).toFixed(0);
        var y_frame = ((this.naturalHeight / $img.height()) * y).toFixed(0);

        var x_center_frame = this.naturalWidth / 2 + x_offset_frame;
        var y_center_frame = this.naturalHeight / 2 + y_offset_frame;

        var x_frame_final = x_frame - x_center_frame;
        var y_frame_final = y_center_frame - y_frame;

        // Get polar coordinates
        var angle_frame =
          (Math.atan2(y_frame_final, x_frame_final) * 180) / Math.PI;
        var dist_frame = Math.sqrt(
          x_frame_final * x_frame_final + y_frame_final * y_frame_final
        );

        console.log(dist_frame.toFixed(3) + " " + angle_frame.toFixed(3));

        // copy to clipboard
        var dummy = document.createElement("textarea");
        document.body.appendChild(dummy);
        dummy.value = dist_frame.toFixed(3) + " " + angle_frame.toFixed(3);
        dummy.select();
        document.execCommand("copy");
        document.body.removeChild(dummy);

        //=============================================================

        prev_cur_x = x_frame_final;
        prev_cur_y = y_frame_final;
      });
    });
  }
};
