import os,pytest
pytestmark=pytest.mark.skipif("HIL_PORT" not in os.environ,reason="requires connected STM32 board")
def test_hil_placeholder():
    # Real transport tests use device_cli and HIL_PORT.
    assert os.environ["HIL_PORT"]
