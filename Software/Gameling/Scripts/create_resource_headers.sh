#!/usr/bin/env bash

cd Resources || exit;

resources_source="../Application/resources.c"
resources_headers="../Application/resources.h"

rm ${resources_source} ${resources_headers}

printf '#pragma once\n\n#include <stdint.h>\n#include <stddef.h>\n\n' > ${resources_headers}
printf '#include "resources.h"\n\n' > ${resources_source}

for filename in *; do

  echo "Converting ${filename}";

  escaped_filename="${filename//./_}"
  file_size=$(stat -f%z "$filename")

  {
    printf "extern const uint8_t %s[%s];\n" "${escaped_filename}" "${file_size}";
  }>> ${resources_headers}

  {
    printf "const uint8_t %s[%s] = {\n" "${escaped_filename}" "${file_size}";
    hexdump -v -e '/1 "0x%02x\n"' "${filename}" | paste -s -d , - | fold -w90 | sed 's/^/    /';
    printf "};\n";
  }>> ${resources_source}

done;
