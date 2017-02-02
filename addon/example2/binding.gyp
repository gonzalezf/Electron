{
  "targets": [
    {
      "target_name": "example1",
      "sources": [
        "example1.cpp"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")"]
    }
  ]
}
