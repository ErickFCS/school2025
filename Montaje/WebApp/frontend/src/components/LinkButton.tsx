import { ReactNode } from "react";
import { useNavigate } from "react-router-dom";


const LinkButton = ({ value, className, children }: { value: string, className?: string, children: ReactNode }) => {
    const navigate = useNavigate();
    const handleClick = (event: React.MouseEvent<HTMLButtonElement, MouseEvent>) => {
        navigate(event.currentTarget.value);
    }
    return (
        <button className={className} onClick={handleClick} value={value}>{children}</button>
    )
}

export default LinkButton;