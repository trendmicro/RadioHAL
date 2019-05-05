#!/bin/bash

PREFIX=$2  # e.g., "CC112X_"

cat <<-EOM
<?xml version="1.0" encoding="ISO-8859-1"?>
<!DOCTYPE configuration SYSTEM "C:/Program Files/Texas Instruments/SmartRF Tools/SmartRF Studio 7/config/xml/configdata.dtd"[]>
<dcpanelconfiguration>
	<registersettings>
EOM

grep -vE '//[^a-z]+halRf' "$1" | grep -oE "halRfWriteReg\([^)]+\)" | grep -oE '\([^)]+\)' | sed 's/[^a-zA-Z0-9_,]//g' | sed 's/'$PREFIX'//g' | grep ',0x' | while read i
do
    left=$(echo $i | cut -d \, -f 1)
    right=$(echo $i | cut -d \, -f 2)

    echo "<Register>"
    echo "  <Name>$left</Name>"
    echo "  <Value>$right</Value>"
    echo "</Register>"
    echo
done 

cat <<-EOM
	</registersettings>
</dcpanelconfiguration>
EOM
