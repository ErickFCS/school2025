import React, { ReactNode } from "react";
import { To, useNavigate } from "react-router-dom";


const LinkTo = ({ to, children }: { to: To, children: ReactNode }) => {
    const navigate = useNavigate();
    const handleClick = (_event: React.MouseEvent<HTMLDivElement, MouseEvent>) => {
        navigate(to);
    };
    return (
        <tr onClick={handleClick}>
            {children}
        </tr>
    );
};

export default LinkTo;
