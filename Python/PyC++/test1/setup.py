from distutils.core import setup,Extension

mine = Extension(name="_test",sources=['_test.so'])

setup(name="test",author="lantian",version="1.0",description="nothing!",packages=['test'],py_modules=['test.py'],ext_modules = [mine])

