DELIMITER //
CREATE PROCEDURE credit_withdraw(IN account_id VARCHAR(20), IN amount DECIMAL(10,2) )
  BEGIN
  DECLARE test1,test2 INT DEFAULT 0;
  START TRANSACTION;
  UPDATE account SET balance=balance-amount WHERE account_id=account_id AND balance >= amount;
  SET test1=ROW_COUNT();
  UPDATE account SET daily_withdrawn=daily_withdrawn+amount WHERE daily_withdrawn < daily_wihtdraw_limit;
  SET test2=ROW_COUNT();
    IF (test1 > 0 AND test2 >0) THEN
      COMMIT;
      INSERT INTO logs(account_account_id,action,amount,action_time) VALUES(first_account,'withdrawal',amount,NOW());
    ELSE
      ROLLBACK;
  END IF;
  END //
DELIMITER ;