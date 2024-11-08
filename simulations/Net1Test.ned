
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.visualizer.common.IntegratedMultiVisualizer;
import inet.visualizer.common.IntegratedVisualizer;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.dsdv.DsdvRouter;
import inet.node.inet.ManetRouter;
import inet.node.gpsr.GpsrRouter;

//
// TODO auto-generated type
//
network Net1Test
{
    @display("bgb=1000,752;bgg=250");
    submodules:
        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=47.32,672.62");
        }
        visualizer: IntegratedVisualizer {
            @display("p=49.01,954.85");
        }
        routingTableRecorder: RoutingTableRecorder {
            parameters:
                @display("p=49.01,863.58997;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            parameters:
                config = xml("<config>"+
                    		   "<interface hosts='Destination' address='172.16.1.201' netmask='255.255.0.0'/>" +
                               "<interface hosts='Source' names='wlan0' address='172.16.1.200' netmask='255.255.0.0'/>" +
                               "<interface hosts='U1' names='wlan0' address='172.16.1.1' netmask='255.255.0.0'/>" +
                               "<interface hosts='U2' names='wlan0' address='172.16.1.2' netmask='255.255.0.0'/>" +
                               "<interface hosts='U3' names='wlan0' address='172.16.1.3' netmask='255.255.0.0'/>" +
                               "<interface hosts='U4' names='wlan0' address='172.16.1.4' netmask='255.255.0.0'/>" +
                               "<interface hosts='U5' names='wlan0' address='172.16.1.5' netmask='255.255.0.0'/>" +
                               "<interface hosts='U6' names='wlan0' address='172.16.1.6' netmask='255.255.0.0'/>" +
                               "<interface hosts='U7' names='wlan0' address='172.16.1.7' netmask='255.255.0.0'/>" +
                               "<interface hosts='U8' names='wlan0' address='172.16.1.8' netmask='255.255.0.0'/>" +
                               "<interface hosts='U9' names='wlan0' address='172.16.1.9' netmask='255.255.0.0'/>" +
                               "<interface hosts='U10' names='wlan0' address='172.16.1.10' netmask='255.255.0.0'/>" +
                               "<interface hosts='U11' names='wlan0' address='172.16.1.11' netmask='255.255.0.0'/>" +
                               "<interface hosts='U12' names='wlan0' address='172.16.1.12' netmask='255.255.0.0'/>" +
                               "<interface hosts='U13' names='wlan0' address='172.16.1.13' netmask='255.255.0.0'/>" +
                               "<interface hosts='U14' names='wlan0' address='172.16.1.14' netmask='255.255.0.0'/>" +
                               "<interface hosts='U15' names='wlan0' address='172.16.1.15' netmask='255.255.0.0'/>" +
                               "<interface hosts='U16' names='wlan0' address='172.16.1.16' netmask='255.255.0.0'/>" +
                               "<interface hosts='U17' names='wlan0' address='172.16.1.17' netmask='255.255.0.0'/>" +
                               "<interface hosts='U18' names='wlan0' address='172.16.1.18' netmask='255.255.0.0'/>" +
                               "<interface hosts='U19' names='wlan0' address='172.16.1.19' netmask='255.255.0.0'/>" +
                               "<interface hosts='U20' names='wlan0' address='172.16.1.20' netmask='255.255.0.0'/>" +
                               "<interface hosts='U21' names='wlan0' address='172.16.1.21' netmask='255.255.0.0'/>" +
                               "<interface hosts='U22' names='wlan0' address='172.16.1.22' netmask='255.255.0.0'/>" +
                               "<interface hosts='U23' names='wlan0' address='172.16.1.23' netmask='255.255.0.0'/>" +
                               "<interface hosts='U24' names='wlan0' address='172.16.1.24' netmask='255.255.0.0'/>" +
                               "<interface hosts='U25' names='wlan0' address='172.16.1.25' netmask='255.255.0.0'/>" +
                               "<interface hosts='U26' names='wlan0' address='172.16.1.26' netmask='255.255.0.0'/>" +
                               "<interface hosts='U27' names='wlan0' address='172.16.1.27' netmask='255.255.0.0'/>" +
                               "<interface hosts='U28' names='wlan0' address='172.16.1.28' netmask='255.255.0.0'/>" +
                               "<interface hosts='U29' names='wlan0' address='172.16.1.29' netmask='255.255.0.0'/>" +
                               "<interface hosts='U30' names='wlan0' address='172.16.1.30' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U31' names='wlan0' address='172.16.1.31' netmask='255.255.0.0'/>" +
                               "<interface hosts='U32' names='wlan0' address='172.16.1.32' netmask='255.255.0.0'/>" +
                               "<interface hosts='U33' names='wlan0' address='172.16.1.33' netmask='255.255.0.0'/>" +
                               "<interface hosts='U34' names='wlan0' address='172.16.1.34' netmask='255.255.0.0'/>" +
                               "<interface hosts='U35' names='wlan0' address='172.16.1.35' netmask='255.255.0.0'/>" +
                               "<interface hosts='U36' names='wlan0' address='172.16.1.36' netmask='255.255.0.0'/>" +
                               "<interface hosts='U37' names='wlan0' address='172.16.1.37' netmask='255.255.0.0'/>" +
                               "<interface hosts='U38' names='wlan0' address='172.16.1.38' netmask='255.255.0.0'/>" +
                               "<interface hosts='U39' names='wlan0' address='172.16.1.39' netmask='255.255.0.0'/>" +
                               "<interface hosts='U40' names='wlan0' address='172.16.1.40' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U41' names='wlan0' address='172.16.1.41' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U42' names='wlan0' address='172.16.1.42' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U43' names='wlan0' address='172.16.1.43' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U44' names='wlan0' address='172.16.1.44' netmask='255.255.0.0'/>" + 
                               "<interface hosts='U45' names='wlan0' address='172.16.1.45' netmask='255.255.0.0'/>" + 
                          "</config>" );
                @display("p=49.01,767.26;is=s");
        }
        Source: ManetRouter {
            @display("p=64,337;i=misc/smartphone,#C01C28,100;is=n");
        }


        Destination: ManetRouter {
            @display("p=850,314;i=misc/smartphone,,100;is=l");
        }

        U2: ManetRouter {
            @display("p=441.75998,40.16;i=misc/smartphone;is=n");
        }


        U3: ManetRouter {
            @display("p=541,290;i=misc/smartphone;is=n");
        }


        U4: ManetRouter {
            @display("p=184,290;i=misc/smartphone;is=n");
        }


        U5: ManetRouter {
            @display("p=339,337;i=misc/smartphone;is=n");
        }


        U6: ManetRouter {
            @display("p=316,546;i=misc/smartphone;is=n");
        }


        U7: ManetRouter {
            @display("p=264,460;i=misc/smartphone;is=n");
        }


        U8: ManetRouter {
            @display("p=425,436;i=misc/smartphone;is=n");
        }


        U9: ManetRouter {
            @display("p=737,113;i=misc/smartphone;is=n");
        }


        U10: ManetRouter {
            @display("p=530.112,62.247997;i=misc/smartphone;is=n");
        }


        U11: ManetRouter {
            @display("p=551,460;i=misc/smartphone;is=n");
        }


        U12: ManetRouter {
            @display("p=64.256,212.84799;i=misc/smartphone;is=n");
        }


        U13: ManetRouter {
            @display("p=116.464,445.776;i=misc/smartphone;is=n");
        }


        U14: ManetRouter {
            @display("p=486,242;i=misc/smartphone;is=n");
        }


        U15: ManetRouter {
            @display("p=771,561;i=misc/smartphone;is=n");
        }


        U16: ManetRouter {
            @display("p=275,40;i=misc/smartphone;is=n");
        }


        U17: ManetRouter {
            @display("p=206,607;i=misc/smartphone;is=n");
        }


        U18: ManetRouter {
            @display("p=637,197;i=misc/smartphone;is=n");
        }


        U19: ManetRouter {
            @display("p=771,426;i=misc/smartphone;is=n");
        }


        U20: ManetRouter {
            @display("p=100.399994,86.343994;i=misc/smartphone;is=n");
        }


        U21: ManetRouter {
            @display("p=425,185;i=misc/smartphone;is=n");
        }


        U22: ManetRouter {
            @display("p=478,561;i=misc/smartphone;is=n");
        }


        U23: ManetRouter {
            @display("p=214,166;i=misc/smartphone;is=n");
        }


        U24: ManetRouter {
            @display("p=645,546;i=misc/smartphone;is=n");
        }


        U25: ManetRouter {
            @display("p=645,309;i=misc/smartphone;is=n");
        }


}
