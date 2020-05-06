from time import sleep
 
from onvif import ONVIFCamera
import zeep
 
XMAX = 1
XMIN = -1
YMAX = 1
YMIN = -1
 
def zeep_pythonvalue(self, xmlvalue):
    return xmlvalue
 
def perform_move(ptz, request, timeout):
    # Start continuous move
    ptz.ContinuousMove(request)
    # Wait a certain time
    sleep(timeout)
    # Stop continuous move
    ptz.Stop({'ProfileToken': request.ProfileToken})
 
 
def absolute_move(pan=0,pan_speed=1,tilt=0,tilt_speed=1):
    # pan = 0
    # pan_speed = 1
    # tilt = 0
    # tilt_speed = 1
    zoom = 1
    zoom_speed = 0.1
 
    mycam = ONVIFCamera('192.168.1.108', 80, 'admin', 'admin123')
    # Create media service object
    media = mycam.create_media_service()
    # Create ptz service object
    ptz = mycam.create_ptz_service()
 
    # Get target profile
    zeep.xsd.simple.AnySimpleType.pythonvalue = zeep_pythonvalue
    media_profile = media.GetProfiles()[0]
 
    # Get PTZ configuration options for getting absolute move range
    request = ptz.create_type('GetConfigurationOptions')
    request.ConfigurationToken = media_profile.PTZConfiguration.token
    # ptz_configuration_options = ptz.GetConfigurationOptions(request)
 
    request = ptz.create_type('AbsoluteMove')
    request.ProfileToken = media_profile.token
    ptz.Stop({'ProfileToken': media_profile.token})

    if request.Position is None:
        request.Position = ptz.GetStatus({'ProfileToken': media_profile.token}).Position
    if request.Speed is None:
        request.Speed = ptz.GetStatus({'ProfileToken': media_profile.token}).Position

    request.Position.PanTilt.x = pan
    request.Speed.PanTilt.x = pan_speed

    request.Position.PanTilt.y = tilt
    request.Speed.PanTilt.y = tilt_speed
 
    request.Position.Zoom = zoom
    request.Speed.Zoom = zoom_speed
    ptz.AbsoluteMove(request)
    # print(request)

    print('finish')
 
 
if __name__ == '__main__':
    absolute_move(0.5,-0.1,0,0)
    sleep(3)
    absolute_move(-0.5,-0.1,0,0)



# from time import sleep
 
# from onvif import ONVIFCamera
# import zeep
 
# # XMAX = 0.5
# # XMIN = -0.5
# # YMAX = 0.5
# # YMIN = -0.5
 
# def zeep_pythonvalue(self, xmlvalue):
#     return xmlvalue
 
# def perform_move(ptz, request, timeout):
#     # Start continuous move
#     ptz.ContinuousMove(request)
#     # Wait a certain time
#     sleep(timeout)
#     # Stop continuous move
#     ptz.Stop({'ProfileToken': request.ProfileToken})
 
# def move_up(ptz, request,speed, timeout=1):
#     print('move up...') 
#     request.Velocity.PanTilt.x = 0
#     request.Velocity.PanTilt.y = speed
#     perform_move(ptz, request, timeout)
 
# def move_down(ptz, request,speed, timeout=1):
#     print('move down...') 
#     request.Velocity.PanTilt.x = 0
#     request.Velocity.PanTilt.y = speed
#     perform_move(ptz, request, timeout)
 
# def move_right(ptz, request,speed, timeout=1):
#     print('move right...') 
#     request.Velocity.PanTilt.x = speed
#     request.Velocity.PanTilt.y = 0
#     perform_move(ptz, request, timeout)
 
# def move_left(ptz, request,speed, timeout=1):
#     print('move left...') 
#     request.Velocity.PanTilt.x = speed
#     request.Velocity.PanTilt.y = 0
#     perform_move(ptz, request, timeout)
 
# # def continuous_move():
# mycam = ONVIFCamera('192.168.1.108', 80, 'admin', 'admin123')
# # Create media service object
# media = mycam.create_media_service()
# # Create ptz service object
# ptz = mycam.create_ptz_service()

# # Get target profile
# zeep.xsd.simple.AnySimpleType.pythonvalue = zeep_pythonvalue
# media_profile = media.GetProfiles()[0]

# # Get PTZ configuration options for getting continuous move range
# request = ptz.create_type('GetConfigurationOptions')
# request.ConfigurationToken = media_profile.PTZConfiguration.token
# ptz_configuration_options = ptz.GetConfigurationOptions(request)

# request = ptz.create_type('ContinuousMove')
# request.ProfileToken = media_profile.token
# ptz.Stop({'ProfileToken': media_profile.token})

# if request.Velocity is None:
#     request.Velocity = ptz.GetStatus({'ProfileToken': media_profile.token}).Position
#     request.Velocity = ptz.GetStatus({'ProfileToken': media_profile.token}).Position
#     request.Velocity.PanTilt.space = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].URI
#     request.Velocity.Zoom.space = ptz_configuration_options.Spaces.ContinuousZoomVelocitySpace[0].URI

# # Get range of pan and tilt
# # NOTE: X and Y are velocity vector
# # global XMAX, XMIN, YMAX, YMIN
# # XMAX = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].XRange.Max
# # XMIN = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].XRange.Min
# # YMAX = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].YRange.Max
# # YMIN = ptz_configuration_options.Spaces.ContinuousPanTiltVelocitySpace[0].YRange.Min
 

 
# if __name__ == '__main__':
#     # continuous_move()
#         # move right
#     # global XMAX, XMIN, YMAX, YMIN
#     for i in range(10):
#         move_right(ptz, request, 1,3)
#         # sleep(0.1)
#         # # move left
#         move_left(ptz, request, -1,3)
#         # sleep(1)

#         # # Move up
#         # move_up(ptz, request, 0.5,0.5)
#         # sleep(1)

#         # # move down
#         # move_down(ptz, request, -0.5,0.5)
#         # sleep(1)
