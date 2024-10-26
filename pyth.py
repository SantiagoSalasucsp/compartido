import sysv_ipc
import time
import sys

# Constants similar to those in the C code
KEY = 0x1111      # Semaphore key
SHM_KEY = 5678    # Shared memory key
SHM_SIZE = 27   # Size of the shared memory

def px_python(text, V):
    try:
        # Access the semaphore using sysv_ipc
        semaphore = sysv_ipc.Semaphore(KEY)

        # Access shared memory
        shared_memory = sysv_ipc.SharedMemory(SHM_KEY,flags=sysv_ipc.IPC_CREAT,mode=0o666,size=27)

        while True:
            # Wait (P operation)
            semaphore.acquire()

            # Read the first 3 characters and check if it matches V - 1
            shmv = int(shared_memory.read(3).decode('utf-8'))

            if shmv == (V - 1):
                # Write V and the provided text to shared memory
                text_final = f"{V:03d}"+text+'\0'
                v_bytes = text_final.encode('utf-8')
                shared_memory.write(v_bytes)

                # Update V for next iteration
                V += 4

            # Release (V operation)
            semaphore.release()

            # Sleep to simulate the C code's loop delay
            time.sleep(1)

    except sysv_ipc.ExistentialError as e:
        print(f"Error accessing shared memory or semaphore: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        # Detach from shared memory
        shared_memory.detach()

# Example usage: python3 px_python.py "your_text" 5
if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 px_python.py <text> <number>")
    else:
        px_python(sys.argv[1], int(sys.argv[2]))