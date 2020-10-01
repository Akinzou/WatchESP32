ICM20600::ICM20600(bool AD0 = true)
{
    if (AD0) 
    {
        DeviceAdress = 0xD2;
    } 

    else 
    {
        DeviceAdress = 0xD4;
    }
}



