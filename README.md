# BÁO CÁO PHÂN TÍCH LỖI VÀ SỬA LỖI DUYỆT MẢNG STRUCT GÓI THUÊ BAO SAAS

> 👤 **Học viên:** Hoàng Công Dũng | **Mã SV:** PTIT-HCM-009
> 🏫 **Môn học:** it102-rl-hoangcongdung

---

## 📊 Sơ đồ thiết kế hệ thống (Flowchart)

> 💡 *Sơ đồ dưới đây được render tự động trực tiếp trên GitHub bằng Mermaid. Bạn cũng có thể tải file **`bt1.drawio`** trong repository này để mở và chỉnh sửa trực tiếp trên [Draw.io (diagrams.net)](https://app.diagrams.net).* 

```mermaid
graph TD
  Start([Bắt đầu vòng lặp duyệt mảng]) --> LoopInit[Khởi tạo i = 0 và total_revenue = 0]
  LoopInit --> CheckBound{i < 4?}
  CheckBound -- Không --> End([Kết thúc & In tổng doanh thu])
  CheckBound -- Đúng --> CheckDays{user_list[i].days_overdue <= 3?}
  CheckDays -- Đúng (Hợp lệ) --> AddFee[total_revenue += user_list[i].monthly_fee]
  AddFee --> PrintValid[In thông tin dòng với trạng thái Hop le]
  CheckDays -- Sai (Quá hạn) --> PrintOverdue[In thông tin dòng với trạng thái Qua han]
  PrintValid --> Inc[i++]
  PrintOverdue --> Inc
  Inc --> CheckBound
```

---

## Nhiệm vụ 1: Phân tích lỗi & Lập bảng Test Cases

Sau khi đọc kỹ mã nguồn legacy trong subscription_report.c, mình đã tìm ra chính xác hai lỗi nghiêm trọng làm lệch số liệu doanh thu thực thu:

Lỗi thứ nhất là việc lập trình viên tiền nhiệm gõ nhầm biến chỉ số mảng trong câu lệnh điều kiện và phép cộng dồn doanh thu. Thay vì dùng user_list[i] để duyệt qua từng phần tử theo biến chạy của vòng lặp for, mã nguồn lại cứng nhắc dùng 'user_list[0]' cho tất cả các bước lặp. Điều này dẫn đến việc chương trình luôn kiểm tra days_overdue và cộng dồn monthly_fee của chính tài khoản đầu tiên (mã 1001) suốt 4 lần chạy.

Lỗi thứ hai là kết quả hiển thị bảng bị sai lệch trạng thái nghiệp vụ. Do kiểm tra sai struct ở phần tử 0, một số tài khoản thực tế đã quá hạn trên 3 ngày (như mã 1004 quá hạn 4 ngày) nhưng vẫn lọt qua điều kiện và bị in nhãn là 'Hop le'.

- Nguyên nhân kỹ thuật: Hardcode chỉ số mảng thành hằng số 0 thay vì biến vòng lặp i.
- Hậu quả nghiệp vụ: Tổng doanh thu bị cộng dồn sai lệch (lặp lại liên tục phí của user_list[0]), gây thất thoát và sai số lớn trong báo cáo kế toán.

| Trường hợp kiểm thử | Dữ liệu đầu vào (user_id, fee, days_overdue) | Kết quả sai thực tế (Legacy Code) | Kết quả đúng mong đợi (Quy chuẩn nghiệp vụ) |
| --- | --- | --- | --- |
| TC01: Tài khoản đúng hạn | 1001, 180000 VND, 0 ngày | Tính 180000 VND, Trạng thái: Hop le | Tính 180000 VND, Trạng thái: Hop le |
| TC02: Tài khoản quá hạn nhẹ | 1002, 90000 VND, 5 ngày | Tính 180000 VND (lặp user 0), Trạng thái: Hop le | Không tính tiền, Trạng thái: Qua han |
| TC03: Tài khoản cận hạn hợp lệ | 1003, 260000 VND, 1 ngày | Tính 180000 VND (lặp user 0), Trạng thái: Hop le | Tính 260000 VND, Trạng thái: Hop le |
| TC04: Tài khoản quá hạn nặng | 1004, 90000 VND, 90000 VND, 4 ngày | Tính 180000 VND (lặp user 0), Trạng thái: Hop le | Không tính tiền, Trạng thái: Qua han |

## Nhiệm vụ 2: Sửa lỗi mã nguồn

Để khắc phục hoàn toàn sự cố trên, mình đã tiến hành viết lại tệp subscription_report.c. Giải pháp cốt lõi là thay thế toàn bộ các vị trí truy cập 'user_list[0]' bên trong vòng lặp for thành 'user_list[i]', giúp chương trình truy vấn đúng thông tin của từng khách hàng theo từng vòng lặp.

Mã nguồn sau khi sửa đã tuân thủ chuẩn ANSI C/C11, biên dịch sạch sẽ không có cảnh báo bằng lệnh 'gcc -Wall subscription_report.c -o subscription_report'.

- Đảm bảo biến i chạy từ 0 đến 3 để duyệt qua đủ 4 phần tử trong mảng struct.
- Sửa câu lệnh điều kiện thành 'user_list[i].days_overdue <= 3' để áp dụng đúng quy tắc nghiệp vụ SaaS.

---

## 📁 Danh sách tệp tin nộp bài trong Repository
- 📝 `bt1.docx`: Báo cáo tài liệu phân tích nghiệp vụ hoàn chỉnh.
- 🎨 `bt1.drawio`: File thiết kế sơ đồ chuẩn theo quy định đề bài (mở trực tiếp bằng [Draw.io](https://app.diagrams.net) hoặc Lucidchart).
- 💻 `subscription_report.c`: Mã nguồn chương trình.
