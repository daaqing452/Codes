"""
Receive data from Pupil using ZMQ.
"""
import zmq
from msgpack import loads
import json
import datetime

context = zmq.Context()
# open a req port to talk to pupil
addr = '127.0.0.1'  # remote ip or localhost
req_port = "50020"  # same as in the pupil remote gui
req = context.socket(zmq.REQ)
req.connect("tcp://{}:{}".format(addr, req_port))
# ask for the sub port
req.send_string('SUB_PORT')
sub_port = req.recv_string()

# open a sub port to listen to pupil
sub = context.socket(zmq.SUB)
sub.connect("tcp://{}:{}".format(addr, sub_port))

# set subscriptions to topics
# recv just pupil/gaze/notifications
# sub.setsockopt_string(zmq.SUBSCRIBE, 'pupil.')
# sub.setsockopt_string(zmq.SUBSCRIBE, 'gaze')
# sub.setsockopt_string(zmq.SUBSCRIBE, 'notify.')
# sub.setsockopt_string(zmq.SUBSCRIBE, 'logging.')
# or everything:
# sub.setsockopt_string(zmq.SUBSCRIBE, '')
sub.setsockopt_string(zmq.SUBSCRIBE, 'surface')


now = datetime.datetime.now()
f = open('record.txt', 'a+')
g = open('rbias.txt', 'w')
last_dic = {}
while True:
    try:
        topic = sub.recv_string()
        msg = sub.recv()
        msg = loads(msg, encoding='utf-8')
        # print("\n{}: {}".format(topic, msg))
        gaze_on_srf = msg['gaze_on_srf']
        '''print(gaze_on_srf)
        print('');
        f.write(str(len(gaze_on_srf)))
        f.write(json.dumps(gaze_on_srf))
        f.write('\n\n')'''
        for dic in gaze_on_srf:
            norm_pos = dic['norm_pos']
            on_srf = dic['on_srf']
            confidence = dic['confidence']
            timestamp = dic['base_data']['timestamp']
            s = str(timestamp) + " " + str(norm_pos[0]) + " " + str(norm_pos[1]) + "\n"
            f.write(s)
            # g.write(s)
            print(s)
            if abs(norm_pos[0]) > 1.5 or abs(1-norm_pos[1]) > 3:
                g.write('O\n')
            '''else:
            	last_dic = dic
        if len(gaze_on_srf) == 0:
            g.write("0\n");'''
    except KeyboardInterrupt:
        break