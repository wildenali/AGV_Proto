void emergency_stop_action();

void emergency_stop_setup()
{
    attachInterrupt(digitalPinToInterrupt(emergency_stop_pin), emergency_stop_action, FALLING);
}

void emergency_stop_action()
{
    // Program untuk menghentikan semua action robot
}
