# The Forgotten Frame:
Lost in the capture is a single frame of something unnatural, a glimpse of another place, darker and colder than here.

### Handout
ForgottenFrame.pcap (MD5 Hash : 9cb2ac078c62bc8f1936d380b9d3756e)

### Flag Format
inctfj{....}

### Author
Rudraagh


### FLAG
inctfj{d4nc35_in_sh4dow5}


### Writeup : 
```py
from scapy.all import *

def extract_icmp_data(pcap_file, output_file):
    packets = rdpcap(pcap_file)
    
    icmp_payloads = []

    for pkt in packets:
        if pkt.haslayer(ICMP) and pkt.haslayer(Raw):
            icmp_payloads.append(pkt[Raw].load)
    
    reassembled_data = b"".join(icmp_payloads)

    with open(output_file, "wb") as f:
        f.write(reassembled_data)
    
    print(f"Extracted data saved to {output_file}")

pcap_file = "chall.pcap"

output_file = "reassembled_image.png"

extract_icmp_data(pcap_file, output_file)
```

Extract png from icmp using the script and fix the corrupted png by fixing the critical chunks of the image.