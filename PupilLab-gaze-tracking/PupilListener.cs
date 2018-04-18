using UnityEngine;
using System;
using System.Threading;
using System.Collections.Generic;
using System.Timers;
using NetMQ; // for NetMQConfig
using NetMQ.Sockets;
using MsgPack;
using Newtonsoft.Json.Linq;


namespace Pupil
{
// Sample:
//{ 
//    "diameter" : 0, 
//    "confidence" : 0, 
//    "projected_sphere" : { 
//        "axes" : [ 55.5000089570384, 55.5000089570384 ], 
//        "angle" : 90, 
//        "center" : [ 249.397085868656, 136.095677317297 ] 
//    }, 
//    "theta" : 0, 
//    "model_id" : 1, 
//    "timestamp" : 16348.113020359, 
//    "model_confidence" : 1, 
//    "method" : "3d c++", 
//    "phi" : 0, 
//    "sphere" : { 
//        "radius" : 12, 
//        "center" : [ -30.5309849672982, -44.9315917465023, 268.108064838663 ] 
//    }, 
//    "diameter_3d" : 0, 
//    "norm_pos" : [ 0.5, 0.5 ], 
//    "id" : 0, 
//    "model_birth_timestamp" : 11561.005596197, 
//    "circle_3d" : { 
//        "radius" : 0, 
//        "center" : [ 0, 0, 0 ], 
//        "normal" : [ 0, 0, 0 ] 
//    }, 
//    "ellipse" : { 
//        "axes" : [ 0, 0 ], 
//        "angle" : 90, 
//        "center" : [ 320, 240 ] 
//    } 
//}

    // Pupil data typea
    [Serializable]
    public class ProjectedSphere
    {
        public double[] axes = new double[] {0,0};
        public double angle;
        public double[] center = new double[] {0,0};
    }
    [Serializable]
    public class Sphere
    {
        public double radius;
        public double[] center = new double[] {0,0,0};
    }
    [Serializable]
    public class Circle3d
    {
        public double radius;
        public double[] center = new double[] {0,0,0};
        public double[] normal = new double[] {0,0,0};
    }
    [Serializable]
    public class Ellipse
    {
        public double[] axes = new double[] {0,0};
        public double angle;
        public double[] center = new double[] {0,0};
    }
    [Serializable]
    public class PupilData3D
    {
        public double diameter;
        public double confidence;
        public ProjectedSphere projected_sphere = new ProjectedSphere();
        public double theta;
        public int model_id;
        public double timestamp;
        public double model_confidence;
        public string method;
        public double phi;
        public Sphere sphere = new Sphere();
        public double diameter_3d;
        public double[] norm_pos = new double[] { 0, 0, 0 };
        public int id;
        public double model_birth_timestamp;
        public Circle3d circle_3d = new Circle3d();
        public Ellipse ellipese = new Ellipse();
    }

    //[Serializable]
    //public class gaze_normals_3d
    //{
    //    public double[] zero = new double[] { 0, 0, 0 };
    //    public double[] one = new double[] { 0, 0, 0 };
    //}

    // Get gaze direction from the json
    [Serializable]
    public class PupilGaze3D
    {
        //public gaze_normals_3d gaze_normals_3d = new gaze_normals_3d();
        public double[] gaze_normals_3d = new double[] { 0, 0, 0 };
    }
}

public class PupilListener : MonoBehaviour
{

    Thread client_thread_;
    private System.Object thisLock_ = new System.Object();
    bool stop_thread_ = false;
    public bool IsLocal = false;
    public string IP_local;// IP of a PC running pupil_capture/_remote
    public string PORT_local; // port of the PC
    public string IP_remote;
    public string PORT_remote;
    public string ID = "gaze"; // target camera
    // ID = "pupil.0"


    Pupil.PupilData3D data_ = new Pupil.PupilData3D();
    Pupil.PupilGaze3D data_zero_ = new Pupil.PupilGaze3D();
    Pupil.PupilGaze3D data_one_ = new Pupil.PupilGaze3D();

    bool zero_flag = true;
    bool one_flag = true;

    Vector3 gaze_normal;
    Vector3 previous_gaze_normal;

    public void get_transform(ref Vector3 pos, ref Quaternion q)
    {
        lock (thisLock_)
        {

            pos = new Vector3(
                        (float)(data_.sphere.center[0]),
                        (float)(data_.sphere.center[1]),
                        (float)(data_.sphere.center[2])
                        );// in [mm]
            q = Quaternion.LookRotation(new Vector3(
            (float)(data_.circle_3d.normal[0]),
            (float)(data_.circle_3d.normal[1]),
            (float)(data_.circle_3d.normal[2])
            ));
        }
    }

    public void get_gaze_direction(ref Quaternion q)
    {
        lock (thisLock_)
        {
            if (zero_flag && one_flag)
            {
                gaze_normal = new Vector3(
                    (float)(data_zero_.gaze_normals_3d[0] + data_one_.gaze_normals_3d[0]) / 2,
                    (float)(data_zero_.gaze_normals_3d[1] + data_one_.gaze_normals_3d[1]) / 2,
                    (float)(data_zero_.gaze_normals_3d[2] + data_one_.gaze_normals_3d[2]) / 2
                    );
            }
            else if (zero_flag && !one_flag)
            {
                gaze_normal = new Vector3(
                    (float)(data_zero_.gaze_normals_3d[0]),
                    (float)(data_zero_.gaze_normals_3d[1]),
                    (float)(data_zero_.gaze_normals_3d[2])
                    );
            }
            else if (!zero_flag && one_flag)
            {
                gaze_normal = new Vector3(
                    (float)(data_one_.gaze_normals_3d[0]),
                    (float)(data_one_.gaze_normals_3d[1]),
                    (float)(data_one_.gaze_normals_3d[2])
                    );
            }
            else
            {
                gaze_normal = previous_gaze_normal;
            }
            if (gaze_normal != Vector3.zero)
            {
                q = Quaternion.LookRotation(gaze_normal);
            }
            else
            {
                q = Quaternion.identity;
            }
            previous_gaze_normal = gaze_normal;
            //Debug.Log("Got gaze direction, q = " + q.ToString());
        }
    }

    void Start()
    {
        Debug.Log("[PUPIL] Start a request thread.");
        client_thread_ = new Thread(NetMQClient);
        client_thread_.Start();
        previous_gaze_normal = new Vector3(0, 0, 0);
    }

    // Client thread which does not block Update()
    void NetMQClient()
    {
        string IPHeader;
        string PORT;
        if (IsLocal)
        {
            IPHeader = ">tcp://" + IP_local + ":";
            PORT = PORT_local;
        }
        else
        {
            IPHeader = ">tcp://" + IP_remote + ":";
            PORT = PORT_remote;
        }
        var timeout = new System.TimeSpan(0, 0, 1); //1sec

        // Necessary to handle this NetMQ issue on Unity editor
        // https://github.com/zeromq/netmq/issues/526
        AsyncIO.ForceDotNet.Force();
        NetMQConfig.ManualTerminationTakeOver();
        NetMQConfig.ContextCreate(true);
        
        string subport="";
        Debug.Log("[PUPIL] [Remote] Connect to the server: " + IPHeader + PORT + ".");
        var requestSocket = new RequestSocket(IPHeader + PORT);
        double t = 0;
        const int N = 1000;
        bool is_connected =false;
        for (int k = 0; k < N; k++)
        {
            var sw = new System.Diagnostics.Stopwatch();
            sw.Start();
            requestSocket.SendFrame("SUB_PORT");
            is_connected = requestSocket.TryReceiveFrameString(timeout, out subport);
            sw.Stop();
            t = t+ sw.Elapsed.Milliseconds;
            //Debug.Log("Round trip time:" + sw.Elapsed + "[sec].");
            if (is_connected == false) break;
        }
        Debug.Log("[PUPIL] Round trip average time:" + t / N + "[msec].");

        requestSocket.Close();

        if (is_connected)
        {
            Debug.Log("[PUPIL] connected");
            var subscriberSocket = new SubscriberSocket( IPHeader + subport);
            subscriberSocket.Subscribe(ID);

            var msg = new NetMQMessage();
            while (/*is_connected &&*/  stop_thread_ == false)
            {
                //Debug.Log("Receive a multipart message.");
                is_connected = subscriberSocket.TryReceiveMultipartMessage(timeout, ref (msg));
                //Debug.Log("[PUPIL] Connected Set:" + is_connected.ToString());
                if (is_connected)
                {
                    //Debug.Log("Unpack a received multipart message.");
                    try
                    {
                        //Debug.Log(msg[1].ConvertToString());
                        var message = MsgPack.Unpacking.UnpackObject(msg[1].ToByteArray());
                        
                        MsgPack.MessagePackObject mmap = message.Value;
                        //Debug.Log(mmap.ToString());
                        lock (thisLock_)
                        {
                            // ******
                            // Do something you want here
                            // ******

                            //data_ = JsonUtility.FromJson<Pupil.PupilData3D>(mmap.ToString());
                            //data__ = JsonUtility.FromJson<Pupil.PupilGaze3D>(mmap.ToString()); //双眼的问题出在此
                            JObject mmm = JObject.Parse(mmap.ToString());
                            //Debug.Log(mmap.ToString());
                            //Debug.Log("lock");
                            foreach (JProperty part in mmm.Properties())
                            {
                                
                                if (part.Name == "gaze_normals_3d")
                                {
                                    string tmp = "{\"gaze_normals_3d\": " + part.Value["0"].ToString() + "}";
                                    //Debug.Log(tmp);
                                    //data_zero_ = JsonUtility.FromJson<Pupil.PupilGaze3D>("{\"gaze_normals_3d\": " + part.Value["0"].ToString() + " }");
                                    //data_one_ = JsonUtility.FromJson<Pupil.PupilGaze3D>("{\"gaze_normals_3d\": " + part.Value["1"].ToString() + " }");
                                    try
                                    {
                                    string zero = part.Value["0"].ToString();
                                    zero = zero.Substring(1,zero.Length-2);
                                    string [] zero_str = zero.Split(',');
                                    //Debug.Log("zero" + zero);
                                    data_zero_.gaze_normals_3d = new double[] {
                                        double.Parse(zero_str[0]),
                                        double.Parse(zero_str[1]),
                                        double.Parse(zero_str[2])};
                                    zero_flag = true;
                                    
                                    }
                                    catch (Exception e) 
                                    {
                                        Debug.Log("[Pupil] eye zero failed");
                                        zero_flag = false;
                                    }
                                    try
                                    {
                                        string one = part.Value["1"].ToString();
                                        one = one.Substring(1, one.Length - 2);
                                        string[] one_str = one.Split(',');
                                        //Debug.Log("one" + one);
                                        data_one_.gaze_normals_3d = new double[] {
                                        double.Parse(one_str[0]),
                                        double.Parse(one_str[1]),
                                        double.Parse(one_str[2])};
                                        one_flag = true;
                                    }
                                    catch (Exception e)
                                    {
                                        Debug.Log("[Pupil] eye one failed");
                                        one_flag = false;
                                    }
                                }
                            }
                        }
                        
                        //Debug.Log(mmap.ToString());
                    }
                    catch
                    {
                        Debug.Log("[PUPIL] Failed to unpack.");
                    }
                }
                else
                {
                    Debug.Log("[PUPIL] Failed to receive a message.");
                    Thread.Sleep(10);
                }
            }
            subscriberSocket.Close();
        }
        else
        {
            Debug.Log("[PUPIL] Failed to connect the server.");
        }

        // Necessary to handle this NetMQ issue on Unity editor
        // https://github.com/zeromq/netmq/issues/526
        Debug.Log("[PUPIL] ContextTerminate.");
        NetMQConfig.ContextTerminate();
    }

    void Update()
    {
        /// Do normal Unity stuff
    }

    void OnApplicationQuit()
    {
        lock (thisLock_)stop_thread_ = true;
        client_thread_.Join();
        Debug.Log("[PUPIL] Quit the thread.");
    }

}