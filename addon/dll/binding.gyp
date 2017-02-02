{
  "targets": [
    {
      "target_name": "file_upload",
      "sources": [ "rainfall.cc", "rainfall_node.cc"],
      "cflags": ["-Wall", "-std=c++11"],
      "include_dirs" : ['../base', "<!(node -e \"require('nan')\")"],
      "conditions": [
        [ 'OS=="mac"', {
            "xcode_settings": {
                'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                'OTHER_LDFLAGS': ['-stdlib=libc++'],
                'MACOSX_DEPLOYMENT_TARGET': '10.7' }
            }
        ]
      ]
    }
  ]
}
