#include "Classes.h"
#include "pre.h"

Provide::Provide() {
  cout << UI::GRAY << "调试:开始初始化Provide" << UI::RESET << endl;
  load_room_info();
  load_stu_sheet();
  load_tec_sheet();
  load_stu_res_sheet();
  load_admin_account();
  ROOM_LIMIT = {20,50,100};
  cout << UI::GRAY << "调试:初始化Provide结束" << UI::RESET << endl;
}

void Provide::load_room_info() // 加载room信息
{
  load_room1_info();
  load_room2_info();
  load_room3_info();
}

void Provide::load_room1_info() {
  fstream file("room1.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开room1.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<int> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(std::stoi(word));
    }
    this->ROOM1_PEONUM_INFO.push_back(info);
  }
  file.close();
  cout << UI::GRAY << "调试:ROOM1_PEONUM_INFO加载完毕" << UI::RESET << endl;
}
void Provide::load_room2_info() {
  fstream file("room2.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开room2.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<int> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(std::stoi(word));
    }
    this->ROOM2_PEONUM_INFO.push_back(info);
  }
  file.close();
  cout << UI::GRAY << "调试:ROOM2_PEONUM_INFO加载完毕" << UI::RESET << endl;
}
void Provide::load_room3_info() {
  fstream file("room3.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开room3.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<int> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(std::stoi(word));
    }
    this->ROOM3_PEONUM_INFO.push_back(info);
  }
  file.close();
  cout << UI::GRAY << "调试:ROOM3_PEONUM_INFO加载完毕" << UI::RESET << endl;
}

void Provide::load_stu_sheet() // 加载学生列表
{
  fstream file("students.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开students.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<std::string> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(word);
    }
    auto stu = std::make_shared<Student>(info[0], info[1], info[2]);
    stu->provider = this;
    this->STUDENT_SHEET[info[0]] = stu; // 写入学生表
  }
  file.close();
  cout << UI::GRAY << "调试:STUDENT_SHEET加载完毕" << UI::RESET << endl;
}

void Provide::load_tec_sheet() // 加载教师列表
{
  fstream file("teacher.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开teacher.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<std::string> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(word);
    }
    auto tec = std::make_shared<Teacher>(info[0], info[1], info[2]);
    tec->provider = this;
    this->TEACHER_SHEET[info[0]] = tec;
  }
  file.close();
  cout << UI::GRAY << "调试:TEACHER_SHEET加载完毕" << UI::RESET << endl;
}

void Provide::load_admin_account()
{
    fstream file("admin.csv", std::ios::in);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开admin.csv"
            << UI::RESET << endl;
        return;
    }
    bool file_empty = false;
    if (file.peek() == fstream::traits_type::eof()) file_empty = true;
    file.seekg(0, std::ios::beg);

    string line;
    std::vector<std::string> info;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (std::getline(ss, word, ',')) {
            info.push_back(word);
        }
    }
    if (file_empty) info = {"0","0"}; //若无内容初始化为00
    ADMIN_ACCOUNT = info;
    ADMIN = std::make_shared<Admin>(info[0], info[1], this);
    file.close();
    cout << UI::GRAY << "调试:ADMIN_ACCOUNT加载完毕" << UI::RESET << endl;
}

bool Provide::check_account_available(const bool &mode,
                                      const string &id) // 0学生1老师
{
  if (!mode)
    if (STUDENT_SHEET.count(id) > 0)
      return false; // 若重复不可行 学生
    else if (TEACHER_SHEET.count(id) > 0)
      return false; // 若重复不可行 老师
  return true;
}

void Provide::add_student_account(const string &id, const string &name,
                                  const string &pwd) {
  auto stu = std::make_shared<Student>(id, name, pwd);
  stu->provider = this;
  STUDENT_SHEET[id] = stu;
}

void Provide::add_teacher_account(const string &id, const string &name,
                                  const string &pwd) {
  auto tec = std::make_shared<Teacher>(id, name, pwd);
  tec->provider = this;
  TEACHER_SHEET[id] = tec;
}

void Provide::load_stu_res_sheet() // 加载预约
{
  fstream file("order.csv", std::ios::in);
  if (!file.is_open()) {
    cerr << UI::RED << "[File Error] 无法打开order.csv" << UI::RESET << endl;
    return;
  }
  file.seekg(0, std::ios::beg); // 初始化读取位置
  string line;

  while (std::getline(file, line)) {

    std::vector<std::string> info;
    std::stringstream ss(line);
    std::string word;

    while (std::getline(ss, word, ',')) {
      info.push_back(word);
    }
    // 预约表 1.订单id（排列=id-1 )2.stu id 3.room id 4.申请day 5时段 6  pass? 7roomsysid 8 dayidd 9timeiddd
    this->RES_SHEET.push_back(std::make_shared<Reservation>(
        info[0], info[1], info[2], info[3], info[4], info[5],std::stoi(info[6]),std::stoi(info[7]), std::stoi(info[8])));

    //未审核订单推送进队列
    if (info[5] == "2") APPLICANT_QUEUE.push(RES_SHEET.back());

    // 订单推送给学生
    std::weak_ptr<Reservation> res_ptr(RES_SHEET.back());
    if (STUDENT_SHEET.count(info[1]) > 0) {
      STUDENT_SHEET[info[1]]->init_add_res_in_sheet(res_ptr);
    } else {
      cerr << UI::RED
           << "[Data Error] 向学生推送订单时出现错误: 学生id[" + info[1] +
                  "]不存在"
           << UI::RESET << endl;
    }
  }
  file.close();
  cout << UI::GRAY << "调试:RES_SHEET加载完毕" << UI::RESET << endl;
}

std::weak_ptr<Student> Provide::get_stu_account(string id) {
  if (STUDENT_SHEET.count(id) > 0) {
    std::weak_ptr<Student> wptr(STUDENT_SHEET[id]);
    return wptr;
  } else {
    std::weak_ptr<Student> wptr;
    return wptr;
  }
}

int Provide::get_stu_num() { return STUDENT_SHEET.size(); }

std::weak_ptr<Teacher> Provide::get_tea_account(string id) {
  if (TEACHER_SHEET.count(id) > 0) {
    std::weak_ptr<Teacher> wptr(TEACHER_SHEET[id]);
    return wptr;
  } else {
    std::weak_ptr<Teacher> wptr;
    return wptr;
  }
}

int Provide::get_tea_num() { return TEACHER_SHEET.size(); }

std::weak_ptr<Reservation> Provide::create_order(string stu_id, string room_id,
                                                 string day, string time, int rm_id, int day_id, int time_id) {
  string id = std::to_string(RES_SHEET.size() + 1);
  // 创建订单
  std::shared_ptr<Reservation> sptr =
      make_shared<Reservation>(id, stu_id, room_id, day, time, "2",rm_id, day_id,time_id);
  RES_SHEET.push_back(sptr);
  APPLICANT_QUEUE.push(sptr);
  std::weak_ptr<Reservation> wptr(sptr);
  return wptr;
}

std::vector<std::shared_ptr<Reservation>> &Provide::get_all_order() {
  return this->RES_SHEET; // 返回RESSHEET的引用
}

int Provide::get_order_num() { return RES_SHEET.size(); }

void Provide::clear_all_res() {
  while (!APPLICANT_QUEUE.empty())
    APPLICANT_QUEUE.pop();
  RES_SHEET.clear();
    //初始化roominfo
  std::vector<std::vector<int>> RESET_ROOM_SHEET;
    for (int i = 0 ; i < 5 ; i++)
    {
        std::vector<int> temp;
	    for (int j = 0 ; j < 2 ; j++)
	    {
            temp.push_back(0);
	    }
        RESET_ROOM_SHEET.push_back(temp);
    }
    ROOM1_PEONUM_INFO = RESET_ROOM_SHEET;
    ROOM2_PEONUM_INFO = RESET_ROOM_SHEET;
    ROOM3_PEONUM_INFO = RESET_ROOM_SHEET;

}

std::vector<std::vector<int>> &Provide::get_room1_sheet() {
  return this->ROOM1_PEONUM_INFO;
}

std::vector<std::vector<int>> &Provide::get_room2_sheet() {
  return this->ROOM2_PEONUM_INFO;
}

std::vector<std::vector<int>> &Provide::get_room3_sheet() {
  return this->ROOM3_PEONUM_INFO;
}

string Provide::check_room_spare(int room, int day, int time) {
  room--;
  day--;
  time--;
  int status;
  if (room == 0)
    status = ROOM1_PEONUM_INFO[day][time];
  if (room == 1)
    status = ROOM2_PEONUM_INFO[day][time];
  if (room == 2)
    status = ROOM3_PEONUM_INFO[day][time];
  string out;
  if (ROOM_LIMIT[room] - status > 10) {
    out = " 空余，当前剩余 ";
    out += std::to_string(ROOM_LIMIT[room] - status);
    out += " 位 ";
  } else if (ROOM_LIMIT[room] - status > 0) {
    out = " 紧张，当前剩余 ";
    out += std::to_string(ROOM_LIMIT[room] - status);
    out += " 位 ";
  } else {
    out = " 满员 ";
  }
  return out;
}

std::shared_ptr<Student> Provide::stu_login(string id, string pwd) {
    if (STUDENT_SHEET.count(id)>0) if (STUDENT_SHEET[id]->m_pwd == pwd) return STUDENT_SHEET[id];
    return nullptr;
}
std::shared_ptr<Teacher> Provide::tea_login(string id, string pwd) {
    if (TEACHER_SHEET.count(id)>0) if (TEACHER_SHEET[id]->m_pwd == pwd) return TEACHER_SHEET[id];
    return nullptr;
}

std::shared_ptr<Admin> Provide::admin_login(string id, string pwd)
{
    if (ADMIN_ACCOUNT[0] == id && ADMIN_ACCOUNT[1] == pwd) return ADMIN;
    return nullptr;
}

std::shared_ptr<Reservation>& Provide::get_applicant_queue()
{
    return APPLICANT_QUEUE.front();
}

int Provide::get_applicant_queue_num()
{
    return APPLICANT_QUEUE.size();
}

void Provide::pass_applicant_in_queue()
{
    APPLICANT_QUEUE.front()->pass_res();
    //开始写入状态表格
    std::vector<std::vector<int>>* targetArray = nullptr;

    switch (APPLICANT_QUEUE.front()->m_room_sys_id) {
    case 1: targetArray = &this->ROOM1_PEONUM_INFO; break;
    case 2: targetArray = &this->ROOM2_PEONUM_INFO; break;
    case 3: targetArray = &this->ROOM3_PEONUM_INFO; break;
    default: return; // 无效选择
    }
    if (ROOM_LIMIT[APPLICANT_QUEUE.front()->m_room_sys_id-1]>(*targetArray)[APPLICANT_QUEUE.front()->m_day_sys_id][APPLICANT_QUEUE.front()->m_time_sys_id])
    {
        (*targetArray)[APPLICANT_QUEUE.front()->m_day_sys_id][APPLICANT_QUEUE.front()->m_time_sys_id]++;
    }else
    {
        APPLICANT_QUEUE.front()->denied_res(); //人满拒绝订单
    }
    APPLICANT_QUEUE.pop();
    
}

void Provide::deny_applicant_in_queue()
{
    APPLICANT_QUEUE.front()->denied_res();
    APPLICANT_QUEUE.pop();
}

void Provide::skip_applicant_in_queue()
{
    APPLICANT_QUEUE.pop();
}

void Provide::cancel_order(std::shared_ptr<Reservation> ws)
{
	//判断ws是否通过
    if (ws->m_pass == "1")
    {
	    //找到对应的地方
        std::vector<std::vector<int>>*  targetArray = nullptr;
        switch (ws->m_room_sys_id) {
        case 1: targetArray = &this->ROOM1_PEONUM_INFO; break;
        case 2: targetArray = &this->ROOM2_PEONUM_INFO; break;
        case 3: targetArray = &this->ROOM3_PEONUM_INFO; break;
        default: return; // 无效选择
        }
        if ((*targetArray)[ws->m_day_sys_id][ws->m_time_sys_id]>0)
        {
            (*targetArray)[ws->m_day_sys_id][ws->m_time_sys_id]--;
        }
    }
    ws->cancel_res();
}

void Provide::save_all()
{
    save_room_info();
    save_stu_res_sheet();
    save_stu_sheet();
    save_tec_sheet();
    save_admin_account();
}


void Provide::save_room_info()
{
    save_room1_info();
    save_room2_info();
    save_room3_info();
}

void Provide::save_room1_info()
{
    fstream file("room1.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开room1.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置
    for (const auto& row : ROOM1_PEONUM_INFO) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i] << (i == row.size() - 1 ? "" : ",");
        }
        file << "\n"; // 每一行 vector 结束后换行
    }
    file.close();
    cout << UI::GRAY << "调试:ROOM1_PEONUM_INFO保存完毕" << UI::RESET << endl;
}

void Provide::save_room2_info()
{
    fstream file("room2.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开room2.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置
    for (const auto& row : ROOM2_PEONUM_INFO) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i] << (i == row.size() - 1 ? "" : ",");
        }
        file << "\n"; // 每一行 vector 结束后换行
    }
    file.close();
    cout << UI::GRAY << "调试:ROOM2_PEONUM_INFO保存完毕" << UI::RESET << endl;

}

void Provide::save_room3_info()
{
    fstream file("room3.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开room3.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置
    for (const auto& row : ROOM3_PEONUM_INFO) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i] << (i == row.size() - 1 ? "" : ",");
        }
        file << "\n"; // 每一行 vector 结束后换行
    }
    file.close();
    cout << UI::GRAY << "调试:ROOM3_PEONUM_INFO保存完毕" << UI::RESET << endl;
}

void Provide::save_stu_res_sheet()
{
    fstream file("order.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开order.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置


    for (const auto& row : RES_SHEET) {
        file << row->m_r_id << "," << row->m_stu_id << "," << row->m_room_id << "," << row->m_day << "," << row->m_time << "," << row->m_pass << "," << row->m_room_sys_id << "," << row->m_day_sys_id << "," << row->m_time_sys_id;
		file << "\n"; // 每一行结束后换行
    }
    
	file.close();
    cout << UI::GRAY << "调试:RES_SHEET保存完毕" << UI::RESET << endl;
}

void Provide::save_stu_sheet()
{
    fstream file("students.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开students.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置
    for (const auto& row :STUDENT_SHEET)
    {
        file << row.second->m_id << "," << row.second->m_name << "," << row.second->m_pwd << "\n";
    }

    file.close();
    cout << UI::GRAY << "调试:STUDENT_SHEET保存完毕" << UI::RESET << endl;
}

void Provide::save_tec_sheet()
{
    fstream file("teacher.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开teacher.csv" << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg); // 初始化读取位置
    for (const auto& row : TEACHER_SHEET)
    {
        file << row.second->m_id << "," << row.second->m_name << "," << row.second->m_pwd << "\n";
    }

    file.close();
    cout << UI::GRAY << "调试:TEACHER_SHEET保存完毕" << UI::RESET << endl;

}

void Provide::save_admin_account()
{
    fstream file("admin.csv", std::ios::out);
    if (!file.is_open()) {
        cerr << UI::RED << "[File Error] 无法打开admin.csv"
            << UI::RESET << endl;
        return;
    }
    file.seekg(0, std::ios::beg);
    file << ADMIN_ACCOUNT[0] << "," << ADMIN_ACCOUNT[1] << "\n";
    file.close();
    cout << UI::GRAY << "调试:ADMIN_ACCOUNT保存完毕" << UI::RESET << endl;
}

