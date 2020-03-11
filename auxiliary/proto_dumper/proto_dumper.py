# SPEXTRO
# File: proto_dumper.py
# Desc:
#   Parse out google protobuf messages logged from flight.
#

import telemetry_pb2 as tpb
import pandas as pd
from flatten_dict import flatten
from google.protobuf.json_format import MessageToDict
from datetime import datetime
import os
import sys


def usage():
    print("python3 proto_dumper.py <LOGFILE>")
    exit(1)

def write_data_collection(data_collection: dict):
    dir_name = "SPEXTRO_LOG_" + datetime.utcnow().strftime("%Y%m%dT%H%M%SZ")
    
    try:
        os.mkdir(dir_name)
    except OSError:
        print("Error creating log csv directory")
        exit(1)

    # Write all log collections to a csv file
    for log_collection_key in data_collection.keys():
        data_collection[log_collection_key].to_csv(os.path.join(dir_name, log_collection_key + ".csv"), index=False)


def make_data_collection(filepath: str):
    # Collection of data frames
    data_collection = dict()

    with open(filepath, "rb+") as log_pb_file:
        while True:
            length_message = log_pb_file.read(2)

            if len(length_message) < 2:
                break

            length_message = int.from_bytes(length_message, "little")
            message_data = log_pb_file.read(length_message)

            if len(message_data) != length_message:
                break

            # Bare sensor log message
            sensor_log_entry = tpb.SensorLog()
            # Deserialize binary pb data
            sensor_log_entry.ParseFromString(message_data)

            # Convert sensor log message data to a dict, flatten that dict to one level
            flat_message_data = flatten(MessageToDict(sensor_log_entry), reducer='underscore')
            # Get name of pb field
            type_name = sensor_log_entry.WhichOneof('data')

            if not type_name in data_collection.keys():
                # Make new DataFrame if one didn't already exist
                data_collection[type_name] = pd.DataFrame([flat_message_data], columns=flat_message_data.keys())
            else:
                # Append data to a existing DataFrame
                data_collection[type_name] = data_collection[type_name].append(flat_message_data, ignore_index=True)
        
    return data_collection


def main():

    if(len(sys.argv) != 2):
        usage()

    filepath_log_file = sys.argv[1]

    data_collection = make_data_collection(filepath_log_file)
    write_data_collection(data_collection)


if __name__ == "__main__":
    main()