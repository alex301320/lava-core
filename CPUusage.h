//
// Created by Surface on 2021/12/18.
//

#ifndef MAIN_CPP_CPUUSAGE_H
#define MAIN_CPP_CPUUSAGE_H
#include <Windows.h>
//ԭ������GetProcessTimes()�������ϴε��õõ��Ľ����������õ�ĳ��ʱ����CPU��ʹ��ʱ��
//C++ ��ȡ�ض����̹涨CPUʹ����  ԭ�ģ�http://blog.csdn.net/liuqx97bb/article/details/52058657
class CPUusage {
private:
    typedef long long          int64_t;
    typedef unsigned long long uint64_t;
    HANDLE _hProcess{};
    int _processor;    //cpu����
    int64_t _last_time{};         //��һ�ε�ʱ��
    int64_t _last_system_time{};


    // ʱ��ת��
    static uint64_t file_time_2_utc(const FILETIME* ftime);

    // ���CPU�ĺ���
    static int get_processor_number();

    //��ʼ��
    void init()
    {
        _last_system_time = 0;
        _last_time = 0;
        _hProcess = nullptr;
    }

    //�رս��̾��
    void clear()
    {
        if (_hProcess) {
            CloseHandle(_hProcess);
            _hProcess = nullptr;
        }
    }

public:
    explicit CPUusage(DWORD ProcessID) {
        init();
        _processor = get_processor_number();
        setpid(ProcessID);
    }
    CPUusage() { init(); _processor = get_processor_number(); }
    ~CPUusage() { clear(); }

    //����ֵΪ���̾�������ж�OpenProcess�Ƿ�ɹ�
    HANDLE setpid(DWORD ProcessID) {
        clear();    //���֮ǰ���ӹ���һ�����̣����ȹر����ľ��
        init();
        return _hProcess= OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, ProcessID);
    }

    //-1 ��Ϊʧ�ܻ�������˳��� ����ɹ����״ε��û᷵��-2����;��setpid������PID���״ε���Ҳ�᷵��-2��
    float get_cpu_usage();
};

#endif //MAIN_CPP_CPUUSAGE_H
