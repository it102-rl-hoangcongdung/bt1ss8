#include <stdio.h>

struct UserAccount {
    int user_id;
    int monthly_fee;
    int days_overdue;
};

int main() {
    // Khai báo mảng struct chứa 4 tài khoản khách hàng
    struct UserAccount user_list[4];
    int i;
    int total_revenue = 0;

    // Khởi tạo dữ liệu mẫu cho danh sách tài khoản
    user_list[0].user_id = 1001;
    user_list[0].monthly_fee = 180000; // Gói Premium
    user_list[0].days_overdue = 0;   // Đúng hạn

    user_list[1].user_id = 1002;
    user_list[1].monthly_fee = 90000;  // Gói Standard
    user_list[1].days_overdue = 5;   // Quá hạn 5 ngày (Không tính doanh thu)

    user_list[2].user_id = 1003;
    user_list[2].monthly_fee = 260000; // Gói Family
    user_list[2].days_overdue = 1;   // Quá hạn 1 ngày (Vẫn hợp lệ)

    user_list[3].user_id = 1004;
    user_list[3].monthly_fee = 90000;  // Gói Standard
    user_list[3].days_overdue = 4;   // Quá hạn 4 ngày (Không tính doanh thu)

    printf("=== DANH SACH TAI KHOAN SUBSCRIPTION ===\n");
    printf("%-10s %-12s %-15s %-15s\n", "MA TK", "PHI THANG", "NO CUOC (NGAY)", "TRANG THAI");
    printf("---------------------------------------------------\n");

    // Duyệt danh sách để kiểm tra trạng thái và tính tổng doanh thu (Đã sửa lỗi index mảng từ 0 thành i)
    for (i = 0; i < 4; i++) {
        if (user_list[i].days_overdue <= 3) {
            total_revenue += user_list[i].monthly_fee;
            printf("%-10d %-12d %-15d %-15s\n", user_list[i].user_id, user_list[i].monthly_fee, user_list[i].days_overdue, "Hop le");
        } else {
            printf("%-10d %-12d %-15d %-15s\n", user_list[i].user_id, user_list[i].monthly_fee, user_list[i].days_overdue, "Qua han");
        }
    }

    printf("---------------------------------------------------\n");
    printf("Tong doanh thu thuc thu: %d VND\n", total_revenue);

    return 0;
}
