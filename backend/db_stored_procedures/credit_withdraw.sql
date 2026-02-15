--Second version of the procedure with error handling. Still under development, copied from debit side still needs modifications for credit.
DELIMITER //
CREATE PROCEDURE credit_withdraw(IN pAccountId VARCHAR(20), IN pAmount DECIMAL(10,2) )
BEGIN
    DECLARE beforeBalance DECIMAL(10,2);
    DECLARE afterBalance DECIMAL(10,2);
    DECLARE todayWithdrawn DECIMAL(10,2);
    DECLARE dailyLimit DECIMAL(10,2);

    DECLARE EXIT HANDLER FOR SQLEXCEPTION
    BEGIN
        -- Handle the error, e.g., log it or return an error message
        ROLLBACK;
        RESIGNAL;
    END;

    IF pAmount <= 0 THEN
        -- Invalid amount, handle accordingly
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid amount';
    END IF;

    START TRANSACTION;

    --Read current values and lock current row to prevent concurrent modifications
    SELECT balance, daily_withdrawn, daily_withdraw_limit
        INTO beforeBalance, todayWithdrawn, dailyLimit
        FROM account
    WHERE account_id = pAccountId
    FOR UPDATE;

    --Account not found
    IF beforeBalance IS NULL THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Account not found';
    END IF;

    --Check sufficient funds
    IF beforeBalance < pAmount THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Insufficient funds';
    END IF;

    --Check daily limit
    IF todayWithdrawn + pAmount > dailyLimit THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Daily withdrawal limit exceeded';
    END IF;

    --Calculate new balance
    SET afterBalance = beforeBalance - pAmount;

    --Update account with new balance and daily withdrawn amount
    UPDATE account
        SET balance = afterBalance, daily_withdrawn = todayWithdrawn + pAmount
    WHERE account_id = pAccountId;

    --Log the withdrawal
    INSERT INTO logs(time,event,amount,description,account_account_id,balance_before,balance_after) VALUES(NOW(),'NOSTO',pAmount,'Debit withdrawal',pAccountId,beforeBalance,afterBalance); 

    COMMIT;
END //
DELIMITER ;