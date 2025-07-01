import { ReactNode } from "react";
import { To, useNavigate } from "react-router-dom";


const LinkTo = ({ to, children }: { to: To, children: ReactNode }) => {
    const navigate = useNavigate();
    const handleClick = () => {
        navigate(to);
    };
    return (
        <tr onClick={handleClick}>
            {children}
        </tr>
    );
};

export default LinkTo;
