package com.ifds.rts;

/**
 * RTSBuffer is the base interface for all RTS formatted 
 * data buffers. It defines no methods. It simply acts as
 * an identifying type for RTS buffers.
 */
public interface RTSBuffer extends java.io.Serializable
{
   public byte[] toByteArray();
}
