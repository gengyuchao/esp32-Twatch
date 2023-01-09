
idf_component_register(
    SRCS "http_ota_main.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES esp_event esp_https_ota app_update protocol_examples_common esp_netif nvs_flash
    EMBED_TXTFILES server_certs/ca_cert.pem
)

