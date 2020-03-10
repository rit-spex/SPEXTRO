import telemetry_pb2 as tpb
from google.protobuf.json_format import MessageToDict
import sys


def dump_file(filepath: str):
    with open(filepath, "rb+") as log_pb_file:
        length_message = int.from_bytes(log_pb_file.read(2), "little")
        sensor_log_entry = tpb.SensorLog()
        sensor_log_entry.ParseFromString(log_pb_file.read(length_message))

        print(MessageToDict(sensor_log_entry))

def main():
    filepath_log_file = sys.argv[1]

    dump_file(filepath_log_file)

if __name__ == "__main__":
    main()